#ifndef DOORS_H
#define DOORS_H

#include "legopathactor.h"

class LegoROI;

class Doors : public LegoPathActor {
public:
	Doors() : m_unk0x154(0), m_ltDoor(NULL), m_rtDoor(NULL), m_unk0x1f4(0) {}

	const char* ClassName() const override { return "Doors"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Doors::ClassName()) ||
			   LegoPathActor::IsA(p_name);
	}

	void ParseAction(char* p_extra) override;
	void Animate(float p_time) override;
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override;
	virtual MxFloat VTable0xcc(float p_time);

	// Doors::`scalar deleting destructor'

private:
	undefined4 m_unk0x154;
	MxFloat m_unk0x158;
	LegoROI* m_ltDoor;
	LegoROI* m_rtDoor;
	MxMatrix m_ltDoorLocal;
	MxMatrix m_rtDoorLocal;
	MxFloat m_unk0x1f4;
};

#endif // DOORS_H
