#include "mxsoundpresenter.h"

#include "mxmisc.h"
#include "mxsoundmanager.h"

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
