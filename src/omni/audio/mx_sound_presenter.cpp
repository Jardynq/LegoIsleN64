#include "mx_sound_presenter.h"

#include "mx_misc.h"
#include "mx_sound_manager.h"

void MxSoundPresenter::Destroy(MxBool p_fromDestructor) {
	if (MSoundManager()) {
		MSoundManager()->UnregisterPresenter(*this);
	}

	m_criticalSection.Enter();
	MxMediaPresenter::Init();
	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		MxMediaPresenter::Destroy(FALSE);
	}
}

MxResult MxSoundPresenter::AddToManager() {
	MxResult ret = FAILURE;

	if (MSoundManager()) {
		ret = SUCCESS;
		MSoundManager()->RegisterPresenter(*this);
	}

	return ret;
}
