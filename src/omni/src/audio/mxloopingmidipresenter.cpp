#include "mxloopingmidipresenter.h"

#include "mxdssound.h"
#include "mxmisc.h"
#include "mxmusicmanager.h"

void MxLoopingMIDIPresenter::StreamingTickle() {
	if (m_action->GetLoopCount()) {
		MxMIDIPresenter::StreamingTickle();
		return;
	}

	if (!m_chunk) {
		m_chunk = NextChunk();
		return;
	}

	if (m_chunk->GetTime() + m_action->GetDuration() <=
		m_action->GetElapsedTime()) {
		ProgressTickleState(e_done);
	}
}

void MxLoopingMIDIPresenter::DoneTickle() {
	if (m_action->GetLoopCount()) {
		MxMIDIPresenter::DoneTickle();
	} else {
		EndAction();
	}
}

MxResult MxLoopingMIDIPresenter::PutData() {
	m_criticalSection.Enter();

	if (m_currentTickleState == e_streaming && m_chunk &&
		!MusicManager()->GetMIDIInitialized()) {
		SetVolume(((MxDSSound*) m_action)->GetVolume());
		MusicManager()->InitializeMIDI(
			m_chunk->GetData(),
			!m_action->GetLoopCount() ? -1 : m_action->GetLoopCount()
		);
	}

	m_criticalSection.Leave();
	return SUCCESS;
}
