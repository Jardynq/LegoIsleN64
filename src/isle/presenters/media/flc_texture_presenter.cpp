#include "flc_texture_presenter.h"

#include "misc.h"
#include "mx_ds_action.h"

LegoFlcTexturePresenter::LegoFlcTexturePresenter() {
	Init();
}

void LegoFlcTexturePresenter::Init() {
}

void LegoFlcTexturePresenter::StartingTickle() {
	MxU16 extraLength = 0;
	char* pp = nullptr;
	char extraCopy[128];
	m_action->GetExtra(extraLength, pp);

	if (pp != NULL) {
		strcpy(extraCopy, pp);
		strcat(extraCopy, ".gif");
	}

	MxFlcPresenter::StartingTickle();
}

void LegoFlcTexturePresenter::PutFrame() {
	MxFlcPresenter::PutFrame();
}
