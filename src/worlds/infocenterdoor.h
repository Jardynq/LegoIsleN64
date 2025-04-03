#ifndef INFOCENTERDOOR_H
#define INFOCENTERDOOR_H

#include "legogamestate.h"
#include "legoworld.h"

class LegoControlManagerNotificationParam;

class InfocenterDoor : public LegoWorld {
public:
	InfocenterDoor();
	~InfocenterDoor() override;

	MxLong Notify(MxParam& p_param) override;

	MxBool VTable0x5c() override { return TRUE; }

	static const char* ClassName() { return "InfocenterDoor"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, InfocenterDoor::ClassName()) ||
			   LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	// InfocenterDoor::`scalar deleting destructor'

private:
	LegoGameState::Area m_destLocation;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);
};

#endif // INFOCENTERDOOR_H
