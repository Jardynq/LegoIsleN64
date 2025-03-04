#include "mxmediapresenter.h"

#include "mxactionnotificationparam.h"
#include "mxautolock.h"
#include "mxcompositepresenter.h"
#include "mxdssubscriber.h"
#include "mxmisc.h"
#include "mxnotificationmanager.h"
#include "mxstreamchunk.h"
#include "mxtimer.h"

void MxMediaPresenter::Init() {
	this->m_subscriber = NULL;
	this->m_loopingChunks = NULL;
	this->m_loopingChunkCursor = NULL;
	this->m_currentChunk = NULL;
}

void MxMediaPresenter::Destroy(MxBool p_fromDestructor) {
	{
		AUTOLOCK(m_criticalSection);

		if (m_currentChunk && m_subscriber) {
			m_subscriber->FreeDataChunk(m_currentChunk);
		}

		if (m_subscriber) {
			delete m_subscriber;
		}

		if (m_loopingChunkCursor) {
			delete m_loopingChunkCursor;
		}

		if (m_loopingChunks) {
			MxStreamChunkListCursor cursor(m_loopingChunks);
			MxStreamChunk* chunk;

			while (cursor.Next(chunk)) {
				chunk->Release();
			}

			delete m_loopingChunks;
		}

		Init();
	}

	if (!p_fromDestructor) {
		MxPresenter::Destroy();
	}
}

MxStreamChunk* MxMediaPresenter::CurrentChunk() {
	MxStreamChunk* chunk = NULL;

	if (m_subscriber) {
		chunk = m_subscriber->PeekData();

		if (chunk && chunk->GetChunkFlags() & DS_CHUNK_BIT3) {
			m_action->SetFlags(m_action->GetFlags() | MxDSAction::c_bit7);
			m_subscriber->PopData();
			m_subscriber->FreeDataChunk(chunk);
			chunk = NULL;
			ProgressTickleState(e_done);
		}
	}

	return chunk;
}

MxStreamChunk* MxMediaPresenter::NextChunk() {
	MxStreamChunk* chunk = NULL;

	if (m_subscriber) {
		chunk = m_subscriber->PopData();

		if (chunk && chunk->GetChunkFlags() & DS_CHUNK_BIT3) {
			m_action->SetFlags(m_action->GetFlags() | MxDSAction::c_bit7);
			m_subscriber->FreeDataChunk(chunk);
			chunk = NULL;
			ProgressTickleState(e_done);
		}
	}

	return chunk;
}

MxResult MxMediaPresenter::StartAction(
	MxStreamController* p_controller,
	MxDSAction* p_action
) {
	MxResult result = FAILURE;
	AUTOLOCK(m_criticalSection);

	if (MxPresenter::StartAction(p_controller, p_action) == SUCCESS) {
		if (m_action->GetFlags() & MxDSAction::c_looping) {
			m_loopingChunks = new MxStreamChunkList;
			m_loopingChunkCursor = new MxStreamChunkListCursor(m_loopingChunks);

			if (!m_loopingChunks && !m_loopingChunkCursor) {
				goto done;
			}
		}

		if (p_controller) {
			m_subscriber = new MxDSSubscriber;

			if (!m_subscriber || m_subscriber->Create(
									 p_controller,
									 p_action->GetObjectId(),
									 p_action->GetUnknown24()
								 ) != SUCCESS) {
				goto done;
			}
		}

		result = SUCCESS;
	}

done:
	return result;
}

void MxMediaPresenter::EndAction() {
	AUTOLOCK(m_criticalSection);

	if (!m_action) {
		return;
	}

	m_currentChunk = NULL;

	if (m_action->GetFlags() & MxDSAction::c_world &&
		(!m_compositePresenter || !m_compositePresenter->VTable0x64(2))) {
		MxPresenter::Enable(FALSE);
		SetTickleState(e_idle);
	} else {
		MxDSAction* action = m_action;
		MxPresenter::EndAction();

		if (m_subscriber) {
			delete m_subscriber;
			m_subscriber = NULL;
		}

		if (action && action->GetOrigin()) {
			NotificationManager()->Send(
				action->GetOrigin(),
				MxEndActionNotificationParam(
					c_notificationEndAction,
					this,
					action,
					FALSE
				)
			);
		}
	}
}

MxResult MxMediaPresenter::Tickle() {
	AUTOLOCK(m_criticalSection);

	CurrentChunk();

	return MxPresenter::Tickle();
}

void MxMediaPresenter::StreamingTickle() {
	if (!m_currentChunk) {
		m_currentChunk = NextChunk();

		if (m_currentChunk) {
			if (m_currentChunk->GetChunkFlags() & DS_CHUNK_END_OF_STREAM) {
				m_subscriber->FreeDataChunk(m_currentChunk);
				m_currentChunk = NULL;
				ProgressTickleState(e_repeating);
			} else if (m_action->GetFlags() & MxDSAction::c_looping) {
				LoopChunk(m_currentChunk);

				if (!IsEnabled()) {
					m_subscriber->FreeDataChunk(m_currentChunk);
					m_currentChunk = NULL;
				}
			}
		}
	}
}

void MxMediaPresenter::RepeatingTickle() {
	if (IsEnabled() && !m_currentChunk) {
		if (m_loopingChunkCursor) {
			if (!m_loopingChunkCursor->Next(m_currentChunk)) {
				m_loopingChunkCursor->Next(m_currentChunk);
			}
		}

		if (m_currentChunk) {
			MxLong time = m_currentChunk->GetTime();
			if (time <= m_action->GetElapsedTime() % m_action->GetLoopCount()) {
				ProgressTickleState(e_freezing);
			}
		} else {
			if (m_action->GetElapsedTime() >=
				m_action->GetStartTime() + m_action->GetDuration()) {
				ProgressTickleState(e_freezing);
			}
		}
	}
}

void MxMediaPresenter::DoneTickle() {
	ProgressTickleState(e_idle);
	EndAction();
}

void MxMediaPresenter::LoopChunk(MxStreamChunk* p_chunk) {
	MxStreamChunk* chunk = new MxStreamChunk;

	MxU32 length = p_chunk->GetLength();
	chunk->SetLength(length);
	chunk->SetData(new MxU8[length]);
	chunk->SetTime(p_chunk->GetTime());

	memcpy(chunk->GetData(), p_chunk->GetData(), chunk->GetLength());
	m_loopingChunks->Append(chunk);
}

void MxMediaPresenter::Enable(MxBool p_enable) {
	if (IsEnabled() != p_enable) {
		MxPresenter::Enable(p_enable);

		if (p_enable) {
			MxLong time = Timer()->GetTime();
			m_action->SetUnknown90(time);
			SetTickleState(e_repeating);
		} else {
			if (m_loopingChunkCursor) {
				m_loopingChunkCursor->Reset();
			}
			m_currentChunk = NULL;
			SetTickleState(e_done);
		}
	}
}
