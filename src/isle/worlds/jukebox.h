#pragma once

#include "gamestate.h"
#include "state.h"
#include "world.h"

class LegoControlManagerNotificationParam;

class JukeBoxState : public LegoState {
public:
	enum Music {
		e_pasquell = 0,
		e_right,
		e_decal,
		e_wallis,
		e_nelson,
		e_torpedos
	};

	JukeBoxState() : m_music(e_pasquell), m_active(FALSE) {}

	MxBool IsSerializable() override { return FALSE; }

	static const char* ClassName() { return "JukeBoxState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, JukeBoxState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	// JukeBoxState::`scalar deleting destructor'

	Music m_music;
	MxU32 m_active;
};

class JukeBox : public LegoWorld {
public:
	JukeBox();
	~JukeBox() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	MxBool VTable0x5c() override { return TRUE; }

	static const char* ClassName() { return "JukeBox"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, JukeBox::ClassName()) || LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	// JukeBox::`scalar deleting destructor'

private:
	MxBool HandleControl(LegoControlManagerNotificationParam& p_param);

	LegoGameState::Area m_destLocation;
	JukeBoxState* m_state;
	undefined2 m_unk0x100;
};

