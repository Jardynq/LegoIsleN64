#ifndef INFOCENTER_H
#define INFOCENTER_H

#include "actionsfwd.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"
#include "misc.h"
#include "mxrect32.h"
#include "radio.h"

class MxNotificationParam;
class MxStillPresenter;
class LegoControlManagerNotificationParam;

class InfocenterState : public LegoState {
public:
	InfocenterState();
	~InfocenterState() override;

	MxBool IsSerializable() override { return FALSE; }

	const char* ClassName() const override { return "InfocenterState"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, InfocenterState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	MxS16 GetMaxNameLength() { return sizeOfArray(m_letters); }
	MxStillPresenter* GetNameLetter(MxS32 p_index) {
		return m_letters[p_index];
	}
	void SetNameLetter(MxS32 p_index, MxStillPresenter* p_letter) {
		m_letters[p_index] = p_letter;
	}

	MxBool HasRegistered() { return m_letters[0] != NULL; }

	InfomainScript::Script GetNextLeaveDialogue() {
		return (InfomainScript::Script
		) m_leaveDialogue[GameState()->GetCurrentAct()]
			.Next();
	}

	// TODO: These probably don't exist according to BETA
	Playlist& GetExitDialogueAct1() { return m_exitDialogueAct1; }
	Playlist& GetExitDialogueAct23() { return m_exitDialogueAct23; }
	Playlist& GetReturnDialogue(LegoGameState::Act p_act) {
		return m_returnDialogue[p_act];
	}
	Playlist& GetLeaveDialogue(LegoGameState::Act p_act) {
		return m_leaveDialogue[p_act];
	}
	Playlist& GetBricksterDialogue() { return m_bricksterDialogue; }
	MxU32 GetUnknown0x74() { return m_unk0x74; }

	void SetUnknown0x74(MxU32 p_unk0x74) { m_unk0x74 = p_unk0x74; }

	// InfocenterState::`scalar deleting destructor'

	// TODO: Most likely getters/setters are not used according to BETA.

	Playlist m_exitDialogueAct1;
	Playlist m_exitDialogueAct23;
	Playlist m_returnDialogue[3];
	Playlist m_leaveDialogue[3];
	Playlist m_bricksterDialogue;
	MxU32 m_unk0x74;
	MxStillPresenter* m_letters[7];
};

struct InfocenterMapEntry {
	InfocenterMapEntry();

	MxStillPresenter* m_destCtl;
	undefined4 m_unk0x04;
	MxRect32 m_area;
};

class Infocenter : public LegoWorld {
public:
	enum Cutscene {
		e_noIntro = -1,
		e_legoMovie,
		e_mindscapeMovie,
		e_introMovie,
		e_outroMovie,
		e_badEndMovie,
		e_goodEndMovie
	};

	enum Character {
		e_noCharacter = 0,
		e_pepper,
		e_mama,
		e_papa,
		e_nick,
		e_laura
	};

	Infocenter();
	~Infocenter() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	const char* ClassName() const override { return "Infocenter"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Infocenter::ClassName()) ||
			   LegoWorld::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void ReadyWorld() override;
	MxBool VTable0x5c() override;
	MxBool Escape() override;
	void Enable(MxBool p_enable) override;

	// Infocenter::`scalar deleting destructor'

private:
	void InitializeBitmaps();

	MxLong HandleKeyPress(MxS8 p_key);
	MxU8 HandleMouseMove(MxS32 p_x, MxS32 p_y);
	MxU8 HandleButtonUp(MxS32 p_x, MxS32 p_y);
	MxU8 HandleControl(LegoControlManagerNotificationParam& p_param);
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);
	MxLong HandleNotification0(MxNotificationParam& p_param);

	void UpdateFrameHot(MxBool p_display);
	void Reset();

	void PlayCutscene(Cutscene p_entityId, MxBool p_scale);
	void StopCutscene();

	void FUN_10070d10(MxS32 p_x, MxS32 p_y);

	void StartCredits();
	void StopCredits();

	void PlayAction(InfomainScript::Script p_script);
	void StopCurrentAction();

	void PlayBookAnimation();
	void StopBookAnimation();

	InfomainScript::Script m_currentInfomainScript;
	MxS16 m_selectedCharacter;
	InfocenterState* m_infocenterState;
	LegoGameState::Area m_destLocation;
	Cutscene m_currentCutscene;
	Radio m_radio;
	MxStillPresenter* m_unk0x11c;
	InfocenterMapEntry m_glowInfo[7];
	MxS16 m_unk0x1c8;
	MxStillPresenter* m_frame;
	MxS16 m_infoManDialogueTimer;
	MxS16 m_bookAnimationTimer;
	MxU16 m_unk0x1d4;
	MxS16 m_unk0x1d6;
};

#endif // INFOCENTER_H
