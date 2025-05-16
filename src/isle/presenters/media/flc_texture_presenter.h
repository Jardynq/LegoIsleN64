#pragma once

#include "mx_flc_presenter.h"

class LegoTextureInfo;

class LegoFlcTexturePresenter : public MxFlcPresenter {
public:
	LegoFlcTexturePresenter();

	static const char* HandlerClassName() { return "LegoFlcTexturePresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	void StartingTickle() override;
	void PutFrame() override;

private:
	void Init();
};
