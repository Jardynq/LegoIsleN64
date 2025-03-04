#ifndef RACECAR_H
#define RACECAR_H

#include "islepathactor.h"

class RaceCar : public IslePathActor {
public:
	RaceCar();
	~RaceCar() override;

	const char* ClassName() const override { return "RaceCar"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, RaceCar::ClassName()) ||
			   IslePathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	MxLong HandleClick() override;

	// RaceCar::`scalar deleting destructor'

private:
	// TODO: RaceCar fields
	undefined m_unk0x160[4];
};

#endif // RACECAR_H
