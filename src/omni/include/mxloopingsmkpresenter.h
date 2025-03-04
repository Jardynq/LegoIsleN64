#ifndef MXLOOPINGSMKPRESENTER_H
#define MXLOOPINGSMKPRESENTER_H

#include "mxsmkpresenter.h"

class MxLoopingSmkPresenter : public MxSmkPresenter {
public:
	MxLoopingSmkPresenter();
	~MxLoopingSmkPresenter() override;

	static const char* HandlerClassName() { return "MxLoopingSmkPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

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
