#include "mxwavepresenter.h"

#include "define.h"
#include "mxautolock.h"
#include "mxdsaction.h"
#include "mxdssubscriber.h"
#include "mxutilities.h"

void MxWavePresenter::Init() {
	m_waveFormat = NULL;
	m_chunkLength = 0;
	m_lockSize = 0;
	m_writtenChunks = 0;
	m_started = FALSE;
	m_is3d = FALSE;
	m_paused = FALSE;
}

MxResult MxWavePresenter::AddToManager() {
	MxResult result = MxSoundPresenter::AddToManager();
	Init();
	return result;
}

void MxWavePresenter::Destroy(MxBool p_fromDestructor) {
	if (m_waveFormat) {
		delete[]((MxU8*) m_waveFormat);
	}

	Init();

	if (!p_fromDestructor) {
		MxSoundPresenter::Destroy(FALSE);
	}
}

MxS8 MxWavePresenter::GetPlayedChunks() {
	log_unimpl();
	return -1;
}

MxBool MxWavePresenter::FUN_100b1ba0() {
	return !m_started || GetPlayedChunks() != (MxS8)m_writtenChunks;
}

void MxWavePresenter::WriteToSoundBuffer(void* p_audioPtr, MxU32 p_length) {
	(void)p_audioPtr;
	(void)p_length;
	log_unimpl();
}

void MxWavePresenter::ReadyTickle() {
	MxStreamChunk* chunk = NextChunk();

	if (chunk) {
		m_waveFormat = (WaveFormat*) new MxU8[chunk->GetLength()];
		memcpy(m_waveFormat, chunk->GetData(), chunk->GetLength());
		m_subscriber->FreeDataChunk(chunk);
		ParseExtra();
		ProgressTickleState(e_starting);
	}
}

void MxWavePresenter::StartingTickle() {
	log_unimpl();
}

void MxWavePresenter::StreamingTickle() {
	if (!m_currentChunk) {
		if (!(m_action->GetFlags() & MxDSAction::c_looping)) {
			MxStreamChunk* chunk = CurrentChunk();

			if (chunk && chunk->GetChunkFlags() & DS_CHUNK_END_OF_STREAM &&
				!(chunk->GetChunkFlags() & DS_CHUNK_BIT16)) {
				chunk->SetChunkFlags(chunk->GetChunkFlags() | DS_CHUNK_BIT16);

				m_currentChunk = new MxStreamChunk;
				MxU8* data = new MxU8[m_chunkLength];

				memset(data, m_silenceData, m_chunkLength);

				m_currentChunk->SetLength(m_chunkLength);
				m_currentChunk->SetData(data);
				m_currentChunk->SetTime(chunk->GetTime() + 1000);
				m_currentChunk->SetChunkFlags(DS_CHUNK_BIT1);
			}
		}

		MxMediaPresenter::StreamingTickle();
	}
}

void MxWavePresenter::DoneTickle() {
	log_unimpl();
	MxMediaPresenter::DoneTickle();
}

void MxWavePresenter::LoopChunk(MxStreamChunk* p_chunk) {
	WriteToSoundBuffer(p_chunk->GetData(), p_chunk->GetLength());
	if (IsEnabled()) {
		m_subscriber->FreeDataChunk(p_chunk);
	}
}

MxResult MxWavePresenter::PutData() {
	log_unimpl();
	return SUCCESS;
}

void MxWavePresenter::EndAction() {
	log_unimpl();
	if (m_action) {
		AUTOLOCK(m_criticalSection);
		MxMediaPresenter::EndAction();
	}
}

void MxWavePresenter::SetVolume(MxS32 p_volume) {
	(void)p_volume;
	log_unimpl();
}

void MxWavePresenter::Enable(MxBool p_enable) {
	if (IsEnabled() != p_enable) {
		MxSoundPresenter::Enable(p_enable);

		if (p_enable) {
			m_writtenChunks = 0;
			m_started = FALSE;
		}
	}
}

void MxWavePresenter::ParseExtra() {
	MxSoundPresenter::ParseExtra();

	MxU16 extraLength = 0;
	char* extraData = nullptr;
	m_action->GetExtra(extraLength, extraData);

	if (extraLength) {
		char extraCopy[512];
		memcpy(extraCopy, extraData, extraLength);
		extraCopy[extraLength] = '\0';

		char soundValue[512];
		if (KeyValueStringParse(soundValue, g_strSOUND, extraCopy)) {
			if (!strcmpi(soundValue, "FALSE")) {
				Enable(FALSE);
			}
		}
	}
}

void MxWavePresenter::Pause() {
	if (!m_paused && m_started) {
		m_paused = TRUE;
	}
}

void MxWavePresenter::Resume() {
	log_unimpl();
}
