#pragma once

#include "mx_video_presenter.h"

class MxFlcPresenter : public MxVideoPresenter {
public:
	MxFlcPresenter();
	~MxFlcPresenter() override;

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxFlcPresenter::ClassName()) ||
			   MxVideoPresenter::IsA(p_name);
	}

	static const char* HandlerClassName() { return "MxFlcPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }
};
