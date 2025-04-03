#ifndef RACECAR_H
#define RACECAR_H

#include "islepathactor.h"

class RaceCar : public IslePathActor {
public:
	RaceCar();
	~RaceCar() override;

	static const char* ClassName() { return "RaceCar"; }

	static MxBool IsA(const char* p_name) {
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
