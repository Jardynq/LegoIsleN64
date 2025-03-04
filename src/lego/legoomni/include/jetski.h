#ifndef JETSKI_H
#define JETSKI_H

#include "islepathactor.h"

class LegoControlManagerNotificationParam;

class Jetski : public IslePathActor {
public:
	Jetski();

	const char* ClassName() const override { return "Jetski"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Jetski::ClassName()) ||
			   IslePathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void Animate(float p_time) override;
	MxLong HandleClick() override;
	MxLong HandleControl(LegoControlManagerNotificationParam&) override;
	void Exit() override;

	void ActivateSceneActions();

	MxS16 GetUnknown0x160() { return m_jetskiDashboardStreamId; }

	// Jetski::`scalar deleting destructor'

private:
	void RemoveFromWorld();

	MxS16 m_jetskiDashboardStreamId;
};

#endif // JETSKI_H
