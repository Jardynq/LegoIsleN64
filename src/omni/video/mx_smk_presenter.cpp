#include "mx_smk_presenter.h"

#include "mxpalette.h"

MxSmkPresenter::MxSmkPresenter() {
	Init();
}

MxSmkPresenter::~MxSmkPresenter() {
	Destroy(TRUE);
}

void MxSmkPresenter::Init() {
	SetBit1(FALSE);
	SetBit2(FALSE);
}

void MxSmkPresenter::Destroy(MxBool p_fromDestructor) {
	Init();

	if (!p_fromDestructor) {
		MxVideoPresenter::Destroy(FALSE);
	}
}

MxResult MxSmkPresenter::AddToManager() {
	return MxVideoPresenter::AddToManager();
}

void MxSmkPresenter::Destroy() {
	Destroy(FALSE);
}
