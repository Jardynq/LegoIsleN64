#ifndef BIKE_H
#define BIKE_H

#include "islepathactor.h"

class Bike : public IslePathActor {
public:
	Bike();

	const char* ClassName() const override { return "Bike"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Bike::ClassName()) || IslePathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	MxLong HandleClick() override;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;
	void Exit() override;

	void ActivateSceneActions();

	// Bike::`scalar deleting destructor'

private:
	// TODO: Bike fields
	undefined m_unk0x160[4];
};

#endif // BIKE_H
