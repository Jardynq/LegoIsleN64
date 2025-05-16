#pragma once

#include "mx_flc_presenter.h"

class MxLoopingFlcPresenter : public MxFlcPresenter {
public:
	MxLoopingFlcPresenter();
	~MxLoopingFlcPresenter() override;

	static const char* HandlerClassName() { return "MxLoopingFlcPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	void RepeatingTickle() override;
	MxResult AddToManager() override;
	void Destroy() override;
	void NextFrame() override;
	virtual void VTable0x88();

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);

	MxLong m_elapsedDuration;
};
