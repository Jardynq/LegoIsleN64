#pragma once

#include "action_sfwd.h"
#include "gamestate.h"
#include "named_plane.h"
#include "state.h"
#include "world.h"
#include "radio.h"

class Ambulance;
class Bike;
class DuneBuggy;
class Helicopter;
class Jetski;
class JukeBoxEntity;
class LegoNamedTexture;
class Motocycle;
class LegoPathStructNotificationParam;
class Pizza;
class Pizzeria;
class RaceCar;
class SkateBoard;
class TowTrack;

class Act1State : public LegoState {
public:
	enum ElevatorFloor { c_floor1 = 1, c_floor2, c_floor3 };

	Act1State();

	static const char* ClassName() { return "Act1State"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Act1State::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxBool Reset() override;
	MxResult Serialize(LegoStorage* p_storage) override;

	void PlayCptClickDialogue();
	void StopCptClickDialogue();
	void RemoveActors();
	void PlaceActors();

	MxU32 GetUnknown18() { return m_unk0x018; }
	ElevatorFloor GetElevatorFloor() { return (ElevatorFloor) m_elevFloor; }
	MxU8 GetUnknown21() { return m_unk0x021; }

	void SetUnknown18(MxU32 p_unk0x18) { m_unk0x018 = p_unk0x18; }
	void SetElevatorFloor(ElevatorFloor p_elevFloor) {
		m_elevFloor = p_elevFloor;
	}
	void SetUnknown21(MxU8 p_unk0x21) { m_unk0x021 = p_unk0x21; }

	// Act1State::`scalar deleting destructor'

	// TODO: Most likely getters/setters are not used according to BETA.

	Playlist m_cptClickDialogue;
	IsleScript::Script m_currentCptClickDialogue;
	MxU32 m_unk0x018;
	MxS16 m_elevFloor;
	MxBool m_unk0x01e;
	MxBool m_unk0x01f;
	MxBool m_planeActive;
	undefined m_unk0x021;
	MxBool m_unk0x022;
	undefined m_unk0x023;
	LegoNamedPlane m_motocyclePlane;
	LegoNamedPlane m_bikePlane;
	LegoNamedPlane m_skateboardPlane;
	LegoNamedPlane m_helicopterPlane;
	LegoNamedTexture* m_helicopterWindshield;
	LegoNamedTexture* m_helicopterJetLeft;
	LegoNamedTexture* m_helicopterJetRight;
	Helicopter* m_helicopter;
	LegoNamedPlane m_jetskiPlane;
	LegoNamedTexture* m_jetskiFront;
	LegoNamedTexture* m_jetskiWindshield;
	Jetski* m_jetski;
	LegoNamedPlane m_dunebuggyPlane;
	LegoNamedTexture* m_dunebuggyFront;
	DuneBuggy* m_dunebuggy;
	LegoNamedPlane m_racecarPlane;
	LegoNamedTexture* m_racecarFront;
	LegoNamedTexture* m_racecarBack;
	LegoNamedTexture* m_racecarTail;
	RaceCar* m_racecar;
};

class Isle : public LegoWorld {
public:
	enum { c_playCamAnims = 0x20, c_playMusic = 0x40 };

	Isle();
	~Isle() override;

	MxLong Notify(MxParam& p_param) override;

	MxBool VTable0x5c() override { return TRUE; }

	static const char* ClassName() { return "Isle"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Isle::ClassName()) || LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	void Add(MxCore* p_object) override;
	void VTable0x60() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;
	virtual void VTable0x6c(LegoPathActor* p_actor);

	void SetDestLocation(LegoGameState::Area p_destLocation) {
		m_destLocation = p_destLocation;
	}
	MxBool HasHelicopter() { return m_helicopter != NULL; }

	void FUN_10033350();

	friend class Act1State;

	// Isle::`scalar deleting destructor'

protected:
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param);
	MxLong HandleTransitionEnd();
	void HandleElevatorEndAction();
	void UpdateGlobe();
	void FUN_10032620();
	void CreateState();
	void FUN_10032d30(
		IsleScript::Script p_script,
		JukeboxScript::Script p_music,
		const char* p_cameraLocation,
		MxBool p_und
	);

	Act1State* m_act1state;
	Pizza* m_pizza;
	Pizzeria* m_pizzeria;
	TowTrack* m_towtrack;
	Ambulance* m_ambulance;
	JukeBoxEntity* m_jukebox;
	Helicopter* m_helicopter;
	Bike* m_bike;
	DuneBuggy* m_dunebuggy;
	Motocycle* m_motocycle;
	SkateBoard* m_skateboard;
	RaceCar* m_racecar;
	Jetski* m_jetski;
	Radio m_radio;
	LegoGameState::Area m_destLocation;
};

