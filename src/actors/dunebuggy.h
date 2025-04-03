#ifndef DUNEBUGGY_H
#define DUNEBUGGY_H

#include "islepathactor.h"

class DuneBuggy : public IslePathActor {
public:
	DuneBuggy();

	static const char* ClassName() { return "DuneBuggy"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, DuneBuggy::ClassName()) ||
			   IslePathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void Animate(float p_time) override;
	MxLong HandleClick() override;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param) override;
	void Exit() override;

	void ActivateSceneActions();

	static MxS32 GetColorOffset(const char* p_variable);

	// DuneBuggy::`scalar deleting destructor'

private:
	MxS16 m_dashboard;
	MxFloat m_fuel;
	MxFloat m_time;
};

#endif // DUNEBUGGY_H
