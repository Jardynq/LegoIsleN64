#pragma once

#include "mx_video_presenter.h"

class MxSmkPresenter : public MxVideoPresenter {
public:
	MxSmkPresenter();
	~MxSmkPresenter() override;

	static const char* HandlerClassName() { return "MxSmkPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxSmkPresenter::ClassName()) ||
			   MxVideoPresenter::IsA(p_name);
	}

	MxResult AddToManager() override;
	void Destroy() override;
	virtual void VTable0x88();

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);
};
