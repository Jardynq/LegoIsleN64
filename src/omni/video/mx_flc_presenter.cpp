#include "mx_flc_presenter.h"

#include "mxbitmap.h"
#include "mxpalette.h"

MxFlcPresenter::MxFlcPresenter() {
	SetBit1(FALSE);
	SetBit2(FALSE);
}

MxFlcPresenter::~MxFlcPresenter() {
	MxVideoPresenter::Destroy(FALSE);
}
