#ifndef ELEVATORBOTTOM_H
#define ELEVATORBOTTOM_H

#include "legogamestate.h"
#include "legoworld.h"

class LegoControlManagerNotificationParam;

class ElevatorBottom : public LegoWorld {
public:
	ElevatorBottom();
	~ElevatorBottom() override;

	MxLong Notify(MxParam& p_param) override;

	MxBool VTable0x5c() override { return TRUE; }

	static const char* ClassName() { return "ElevatorBottom"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ElevatorBottom::ClassName()) ||
			   LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	// ElevatorBottom::`scalar deleting destructor'

private:
	LegoGameState::Area m_destLocation;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);
};

#endif // ELEVATORBOTTOM_H
