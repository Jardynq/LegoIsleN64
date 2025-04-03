#include "mx_midi_presenter.h"

#include "mxautolock.h"
#include "mx_ds_sound.h"
#include "mx_ds_subscriber.h"
#include "mx_misc.h"
#include "mx_music_manager.h"

MxMIDIPresenter::MxMIDIPresenter() {
	Init();
}

MxMIDIPresenter::~MxMIDIPresenter() {
	Destroy(TRUE);
}

void MxMIDIPresenter::Init() {
	m_chunk = NULL;
}

void MxMIDIPresenter::Destroy(MxBool p_fromDestructor) {
	if (MusicManager()) {
		MusicManager()->DeinitializeMIDI();
	}

	m_criticalSection.Enter();

	if (m_subscriber && m_chunk) {
		m_subscriber->FreeDataChunk(m_chunk);
	}
	Init();

	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		MxMusicPresenter::Destroy();
	}
}

void MxMIDIPresenter::ReadyTickle() {
	MxStreamChunk* chunk = NextChunk();

	if (chunk) {
		m_subscriber->FreeDataChunk(chunk);
		ParseExtra();
		ProgressTickleState(e_starting);
	}
}

void MxMIDIPresenter::StartingTickle() {
	MxStreamChunk* chunk = CurrentChunk();

	if (chunk && m_action->GetElapsedTime() >= chunk->GetTime()) {
		ProgressTickleState(e_streaming);
	}
}

void MxMIDIPresenter::StreamingTickle() {
	if (m_chunk) {
		ProgressTickleState(e_done);
	} else {
		m_chunk = NextChunk();
	}
}

void MxMIDIPresenter::DoneTickle() {
	if (!MusicManager()->GetMIDIInitialized()) {
		EndAction();
	}
}

void MxMIDIPresenter::Destroy() {
	Destroy(FALSE);
}

MxResult MxMIDIPresenter::PutData() {
	m_criticalSection.Enter();

	if (m_currentTickleState == e_streaming && m_chunk &&
		!MusicManager()->GetMIDIInitialized()) {
		SetVolume(((MxDSSound*) m_action)->GetVolume());

		if (MusicManager()->InitializeMIDI(m_chunk->GetData(), 1) != SUCCESS) {
			EndAction();
		}
	}

	m_criticalSection.Leave();
	return SUCCESS;
}

void MxMIDIPresenter::EndAction() {
	if (m_action) {
		AUTOLOCK(m_criticalSection);

		MxMediaPresenter::EndAction();
		MusicManager()->DeinitializeMIDI();
	}
}

void MxMIDIPresenter::SetVolume(MxS32 p_volume) {
	m_volume = p_volume;
	MusicManager()->SetMultiplier(p_volume);
}
