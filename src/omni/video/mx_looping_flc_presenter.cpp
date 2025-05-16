#include "mx_looping_flc_presenter.h"

#include "mpeg2.h"
#include "mx_ds_action.h"

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
	Init();

	if (!p_fromDestructor) {
		MxFlcPresenter::Destroy(FALSE);
	}
}

void MxLoopingFlcPresenter::NextFrame() {
	if (mpeg2_next_frame(m_video)) {
		m_frame = mpeg2_get_frame(m_video);
	} else {
		mpeg2_rewind(m_video);
		if (mpeg2_next_frame(m_video)) {
			m_frame = mpeg2_get_frame(m_video);
		}
	}

	ProgressTickleState(e_repeating);
}

void MxLoopingFlcPresenter::VTable0x88() {
	if (m_action->GetDuration() < m_elapsedDuration) {
		ProgressTickleState(e_freezing);
	}
}

void MxLoopingFlcPresenter::RepeatingTickle() {
	for (MxS16 i = 0; i < m_unk0x5c; i++) {
		if (m_action->GetElapsedTime() < node->start_time) {
			break;
		}

		VTable0x88();

		if (m_currentTickleState != e_repeating) {
			break;
		}
	}
}

MxResult MxLoopingFlcPresenter::AddToManager() {
	MxResult result = FAILURE;

	if (MxFlcPresenter::AddToManager() == SUCCESS) {
		result = SUCCESS;
	}

	return result;
}

void MxLoopingFlcPresenter::Destroy() {
	Destroy(FALSE);
}
