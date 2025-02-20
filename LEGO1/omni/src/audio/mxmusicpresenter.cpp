#include "mxmusicpresenter.h"

#include "utils.h"
#include "mxmisc.h"
#include "mxmusicmanager.h"


// FUNCTION: LEGO1 0x100c22c0
MxMusicPresenter::MxMusicPresenter() {
	Init();
}

// FUNCTION: LEGO1 0x100c24e0
MxMusicPresenter::~MxMusicPresenter() {
	Destroy(TRUE);
}

// FUNCTION: LEGO1 0x100c2540
void MxMusicPresenter::Init() {
}

// FUNCTION: LEGO1 0x100c2550
void MxMusicPresenter::Destroy(MxBool p_fromDestructor) {
	if (MusicManager()) {
		MusicManager()->UnregisterPresenter(*this);
	}

	m_criticalSection.Enter();
	Init();
	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		MxMediaPresenter::Destroy(FALSE);
	}
}

// FUNCTION: LEGO1 0x100c25a0
MxResult MxMusicPresenter::AddToManager() {
	MxResult result = FAILURE;

	if (MusicManager()) {
		result = SUCCESS;
		MusicManager()->RegisterPresenter(*this);
	}

	return result;
}

// FUNCTION: LEGO1 0x100c25d0
void MxMusicPresenter::Destroy() {
	Destroy(FALSE);
}
