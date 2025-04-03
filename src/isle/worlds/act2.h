#ifndef LEGOACT2_H
#define LEGOACT2_H

#include "act2_brick.h"
#include "gamestate.h"
#include "state.h"
#include "world.h"

class Act2Actor;
class LegoPathStructNotificationParam;
class MxEndActionNotificationParam;

class LegoAct2State : public LegoState {
public:
	LegoAct2State() {
		m_unk0x08 = 0;
		m_enabled = FALSE;
	}
	~LegoAct2State() override {}

	MxBool IsSerializable() override { return FALSE; }

	static const char* ClassName() { return "LegoAct2State"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoAct2State::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	// LegoAct2State::`scalar deleting destructor'

	void SetUnknown0x08(undefined4 p_unk0x08) { m_unk0x08 = p_unk0x08; }

	undefined4 GetUnknown0x08() { return m_unk0x08; }

	// TODO: Most likely getters/setters are not used according to BETA. (?)

	undefined4 m_unk0x08;
	MxBool m_enabled;
};

class LegoAct2 : public LegoWorld {
public:
	LegoAct2();
	~LegoAct2() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;
	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;

	MxBool VTable0x5c() override { return TRUE; }

	void VTable0x60() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	void SetUnknown0x1138(Act2Actor* p_unk0x1138) { m_unk0x1138 = p_unk0x1138; }
	void SetDestLocation(LegoGameState::Area p_destLocation) {
		m_destLocation = p_destLocation;
	}

	MxResult FUN_100516b0();
	void FUN_100517b0();
	MxResult BadEnding();
	MxResult FUN_10052560(
		Act2mainScript::Script p_objectId,
		MxBool p_param2,
		MxBool p_param3,
		Mx3DPointFloat* p_location,
		Mx3DPointFloat* p_direction,
		Mx3DPointFloat* p_param6
	);

	// LegoAct2::`scalar deleting destructor'

private:
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);
	MxLong HandleTransitionEnd();
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param);
	void PlayMusic(JukeboxScript::Script p_objectId);
	void FUN_10051900();
	void FUN_10051960();
	void InitBricks();
	void UninitBricks();
	void SpawnBricks();
	void FUN_10051fa0(MxS32 p_param1);
	void FUN_100521f0(MxS32 p_param1);
	MxResult FUN_10052800();

	Act2Brick m_bricks[10];
	MxU8 m_nextBrick;
	undefined m_unk0x10c1;
	MxBool m_ready;
	undefined4 m_unk0x10c4;
	JukeboxScript::Script m_music;
	LegoAct2State* m_gameState;
	MxS32 m_unk0x10d0;
	// variable name verified by BETA10 0x10014633
	const char* m_siFile;
	LegoROI* m_pepper;
	MxMatrix m_unk0x10dc;
	LegoPathBoundary* m_unk0x1124;
	LegoROI* m_ambulance;
	undefined4 m_unk0x112c;
	undefined4 m_unk0x1130;
	undefined4 m_unk0x1134;
	Act2Actor* m_unk0x1138;
	undefined m_unk0x113c;
	Act2mainScript::Script m_unk0x1140;
	Act2mainScript::Script m_unk0x1144;
	undefined4 m_unk0x1148;
	undefined m_firstBrick;
	undefined m_secondBrick;
	undefined m_thirdBrick;
	undefined m_fourthBrick;
	LegoGameState::Area m_destLocation;
};

#endif // LEGOACT2_H
