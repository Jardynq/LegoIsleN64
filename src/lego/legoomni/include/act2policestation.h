#ifndef ACT2POLICESTATION_H
#define ACT2POLICESTATION_H

#include "legoentity.h"

class Act2PoliceStation : public LegoEntity {
public:
	MxLong Notify(MxParam& p_param) override;

	const char* ClassName() const override { return "Act2PoliceStation"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Act2PoliceStation::ClassName()) ||
			   LegoEntity::IsA(p_name);
	}

	// Act2PoliceStation::`scalar deleting destructor'
};

#endif // ACT2POLICESTATION_H
