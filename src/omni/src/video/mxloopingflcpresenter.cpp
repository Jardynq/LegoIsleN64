#include "mxloopingflcpresenter.h"

#include "mxdsaction.h"
#include "mxdssubscriber.h"

MxLoopingFlcPresenter::MxLoopingFlcPresenter() {
	Init();
}

MxLoopingFlcPresenter::~MxLoopingFlcPresenter() {
	Destroy(TRUE);
}

void MxLoopingFlcPresenter::Init() {
	this->m_elapsedDuration = 0;
	SetBit1(FALSE);
	SetBit2(FALSE);
}

void MxLoopingFlcPresenter::Destroy(MxBool p_fromDestructor) {
	m_criticalSection.Enter();
	Init();
	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		MxFlcPresenter::Destroy(FALSE);
	}
}

void MxLoopingFlcPresenter::NextFrame() {
	MxStreamChunk* chunk = NextChunk();

	if (chunk->GetChunkFlags() & DS_CHUNK_END_OF_STREAM) {
		ProgressTickleState(e_repeating);
	} else {
		LoadFrame(chunk);
		LoopChunk(chunk);
		m_elapsedDuration += m_flcHeader->speed;
	}

	m_subscriber->FreeDataChunk(chunk);
}

void MxLoopingFlcPresenter::VTable0x88() {
	if (m_action->GetDuration() < m_elapsedDuration) {
		ProgressTickleState(e_freezing);
	} else {
		MxStreamChunk* chunk;
		m_loopingChunkCursor->Current(chunk);
		LoadFrame(chunk);
		m_elapsedDuration += m_flcHeader->speed;
	}
}

void MxLoopingFlcPresenter::RepeatingTickle() {
	for (MxS16 i = 0; i < m_unk0x5c; i++) {
		if (!m_loopingChunkCursor->HasMatch()) {
			MxStreamChunk* chunk;
			MxStreamChunkListCursor cursor(m_loopingChunks);

			cursor.Last(chunk);
			MxLong time = chunk->GetTime();

			cursor.First(chunk);

			time -= chunk->GetTime();
			time += m_flcHeader->speed;

			cursor.Reset();
			while (cursor.Next(chunk)) {
				chunk->SetTime(chunk->GetTime() + time);
			}

			m_loopingChunkCursor->Next();
		}

		MxStreamChunk* chunk;
		m_loopingChunkCursor->Current(chunk);

		if (m_action->GetElapsedTime() < chunk->GetTime()) {
			break;
		}

		VTable0x88();

		m_loopingChunkCursor->Next(chunk);

		if (m_currentTickleState != e_repeating) {
			break;
		}
	}
}

MxResult MxLoopingFlcPresenter::AddToManager() {
	MxResult result = FAILURE;
	MxBool locked = FALSE;

	if (MxFlcPresenter::AddToManager() == SUCCESS) {
		m_criticalSection.Enter();
		locked = TRUE;
		result = SUCCESS;
	}

	if (locked) {
		m_criticalSection.Leave();
	}

	return result;
}

void MxLoopingFlcPresenter::Destroy() {
	Destroy(FALSE);
}
