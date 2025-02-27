#include "mxsoundpresenter.h"

#include "utils.h"
#include "mxmisc.h"
#include "mxsoundmanager.h"


// FUNCTION: LEGO1 0x100b1a50
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

// FUNCTION: LEGO1 0x100b1aa0
MxResult MxSoundPresenter::AddToManager() {
	MxResult ret = FAILURE;

	if (MSoundManager()) {
		ret = SUCCESS;
		MSoundManager()->RegisterPresenter(*this);
	}

	return ret;
}
