#ifndef MXLOOPINGSMKPRESENTER_H
#define MXLOOPINGSMKPRESENTER_H

#include "mx_smk_presenter.h"

class MxLoopingSmkPresenter : public MxSmkPresenter {
public:
	MxLoopingSmkPresenter();
	~MxLoopingSmkPresenter() override;

	static const char* HandlerClassName() { return "MxLoopingSmkPresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	void RepeatingTickle() override;
	MxResult AddToManager() override;
	void Destroy() override;
	void NextFrame() override;
	void VTable0x88() override;
	virtual void VTable0x8c();

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);

	MxLong m_elapsedDuration;
};

// MxLoopingSmkPresenter::`scalar deleting destructor'

#endif // MXLOOPINGSMKPRESENTER_H
