#include "infocenter_door.h"

#include "infocenter.h"
#include "infodoor_actions.h"
#include "jukebox.h"
#include "jukebox_actions.h"
#include "control_manager.h"
#include "gamestate.h"
#include "input_manager.h"
#include "legomain.h"
#include "misc.h"
#include "mx_action_notification_param.h"
#include "mx_background_audio_manager.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_transition_manager.h"
#include "scripts.h"

InfocenterDoor::InfocenterDoor() {
	m_destLocation = LegoGameState::e_undefined;

	NotificationManager()->Register(this);
}

InfocenterDoor::~InfocenterDoor() {
	if (InputManager()->GetWorld() == this) {
		InputManager()->ClearWorld();
	}

	ControlManager()->Unregister(this);
	NotificationManager()->Unregister(this);
}

MxResult InfocenterDoor::Create(MxDSAction& p_dsAction) {
	MxResult result = LegoWorld::Create(p_dsAction);
	if (result == SUCCESS) {
		InputManager()->SetWorld(this);
		ControlManager()->Register(this);
	}

	SetIsWorldActive(FALSE);

	GameState()->m_currentArea = LegoGameState::e_infodoor;
	GameState()->StopArea(LegoGameState::e_previousArea);

	return result;
}

MxLong InfocenterDoor::Notify(MxParam& p_param) {
	MxNotificationParam& param = (MxNotificationParam&) p_param;
	MxLong result = 0;
	LegoWorld::Notify(p_param);

	if (m_worldStarted) {
		switch (param.GetNotification()) {
		case c_notificationEndAction:
			if (((MxEndActionNotificationParam&) p_param)
					.GetAction()
					->GetAtomId() == m_atomId) {
				BackgroundAudioManager()->RaiseVolume();
				result = 1;
			}
			break;
		case c_notificationControl:
			result =
				HandleControl((LegoControlManagerNotificationParam&) p_param);
			break;
		case c_notificationTransitioned:
			GameState()->SwitchArea(m_destLocation);
			result = 1;
			break;
		}
	}

	return result;
}

void InfocenterDoor::ReadyWorld() {
	LegoWorld::ReadyWorld();
	PlayMusic(JukeboxScript::c_InformationCenter_Music);
	FUN_10015820(
		FALSE,
		LegoOmni::c_disableInput | LegoOmni::c_disable3d |
			LegoOmni::c_clearScreen
	);
}

MxLong
InfocenterDoor::HandleControl(LegoControlManagerNotificationParam& p_param) {
	MxLong result = 0;

	if (p_param.GetUnknown0x28() == 1) {
		DeleteObjects(&m_atomId, InfodoorScript::c_iic037in_PlayWav, 510);

		switch (p_param.GetClickedObjectId()) {
		case InfodoorScript::c_LeftArrow_Ctl:
			m_destLocation = LegoGameState::e_infoscor;
			TransitionManager()->StartTransition(
				MxTransitionManager::e_mosaic,
				50,
				FALSE,
				FALSE
			);
			result = 1;
			break;
		case InfodoorScript::c_RightArrow_Ctl:
			m_destLocation = LegoGameState::e_elevbott;
			TransitionManager()->StartTransition(
				MxTransitionManager::e_mosaic,
				50,
				FALSE,
				FALSE
			);
			result = 1;
			break;
		case InfodoorScript::c_Info_Ctl:
			m_destLocation = LegoGameState::e_infomain;
			TransitionManager()->StartTransition(
				MxTransitionManager::e_mosaic,
				50,
				FALSE,
				FALSE
			);
			result = 1;
			break;
		case InfodoorScript::c_Door_Ctl:
			if (GameState()->GetActorId() != LegoActor::c_none) {
				InfocenterState* state =
					(InfocenterState*) GameState()->GetState("InfocenterState");
				if (state->HasRegistered()) {
					m_destLocation = LegoGameState::e_unk4;
				} else {
					MxDSAction action;
					action.SetObjectId(InfodoorScript::c_iic007in_PlayWav);
					action.SetAtomId(*g_infodoorScript);
					BackgroundAudioManager()->LowerVolume();
					Start(&action);
					goto done;
				}
			} else {
				MxDSAction action;
				action.SetObjectId(InfodoorScript::c_iic037in_PlayWav);
				action.SetAtomId(*g_infodoorScript);
				BackgroundAudioManager()->LowerVolume();
				Start(&action);
				goto done;
			}

			TransitionManager()->StartTransition(
				MxTransitionManager::e_mosaic,
				50,
				FALSE,
				FALSE
			);

		done:
			result = 1;
			break;
		}
	}

	return result;
}

void InfocenterDoor::Enable(MxBool p_enable) {
	LegoWorld::Enable(p_enable);

	if (p_enable) {
		InputManager()->SetWorld(this);
		SetIsWorldActive(FALSE);
	} else {
		if (InputManager()->GetWorld() == this) {
			InputManager()->ClearWorld();
		}
	}
}

MxBool InfocenterDoor::Escape() {
	DeleteObjects(&m_atomId, InfodoorScript::c_iic037in_PlayWav, 510);
	m_destLocation = LegoGameState::e_infomain;
	return TRUE;
}
