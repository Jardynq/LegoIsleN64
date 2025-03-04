#include "mxmusicpresenter.h"

#include "mxmisc.h"
#include "mxmusicmanager.h"

MxMusicPresenter::MxMusicPresenter() {
	Init();
}

MxMusicPresenter::~MxMusicPresenter() {
	Destroy(TRUE);
}

void MxMusicPresenter::Init() {
}

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

MxResult MxMusicPresenter::AddToManager() {
	MxResult result = FAILURE;

	if (MusicManager()) {
		result = SUCCESS;
		MusicManager()->RegisterPresenter(*this);
	}

	return result;
}

void MxMusicPresenter::Destroy() {
	Destroy(FALSE);
}
