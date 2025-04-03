#ifndef LEGORACEMAP_H
#define LEGORACEMAP_H

#include "legoraceactor.h"

class MxControlPresenter;
class MxStillPresenter;

class LegoRaceMap : public virtual LegoRaceActor {
public:
	LegoRaceMap();
	~LegoRaceMap() override;

	// LegoPathActor vtable
	MxLong Notify(MxParam& p_param) override;
	void ParseAction(char* p_extra) override;
	void Animate(float p_time) override = 0;

	// LegoRaceMap vtable
	virtual void FUN_1005d4b0();

	// LegoRaceMap::`vbase destructor'

	// LegoRaceMap::`scalar deleting destructor'

private:
	MxBool m_unk0x08;
	MxStillPresenter* m_stillPresenter;
	// variable name verified by BETA10 0x100ca82b
	MxControlPresenter* m_Map_Ctl;
	// likely an x-offset of the race map in world space
	float m_unk0x14; // inversely scales the map in x direction (either convert
					 // world->screen
	// space or to control the size)
	float m_unk0x18; // likely a y-offset of the race map in world space
	float m_unk0x1c; // inversely scales the map in y direction (either convert
					 // world->screen
	// space or to control the size)
	float m_unk0x20; // scales the map in x direction (either convert
					 // world->screen space or to
	// change the size)
	float m_unk0x24; // scales the map in y direction (either convert
					 // world->screen space or to
	// change the size)
	float m_unk0x28; // likely an x-offset of the race map in screen space
	float m_unk0x2c; // likely a y-offset of the race map in screen space
	float m_unk0x30;
};

// LegoRaceMap::`vbtable'

// LegoRaceMap::`vbtable'{for `LegoAnimActor'}

// LegoRaceMap::`vbtable'{for `LegoRaceActor'}

#endif // LEGORACEMAP_H
