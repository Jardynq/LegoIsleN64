#include "skateboard.h"

#include "isle.h"
#include "isle_actions.h"
#include "jukebox_actions.h"
#include "animation_manager.h"
#include "control_manager.h"
#include "utils.h"
#include "misc.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_still_presenter.h"
#include "mx_transition_manager.h"
#include "pizza.h"
#include "scripts.h"

SkateBoard::SkateBoard() {
	m_pizzaVisible = FALSE;
	m_maxLinearVel = 15.0;
	m_unk0x150 = 3.5;
	m_unk0x148 = 1;

	NotificationManager()->Register(this);
}

SkateBoard::~SkateBoard() {
	ControlManager()->Unregister(this);
	NotificationManager()->Unregister(this);
}

MxResult SkateBoard::Create(MxDSAction& p_dsAction) {
	MxResult result = IslePathActor::Create(p_dsAction);

	if (result == SUCCESS) {
		m_world = CurrentWorld();
		m_world->Add(this);

		Pizza* pizza = (Pizza*) CurrentWorld()->Find(
			*g_isleScript,
			IsleScript::c_Pizza_Actor
		);
		if (pizza) {
			pizza->SetSkateboard(this);
		}
	}

	return result;
}

void SkateBoard::Exit() {
	if (m_act1state->m_unk0x018 == 3) {
		Pizza* pizza = (Pizza*) CurrentWorld()->Find(
			*g_isleScript,
			IsleScript::c_Pizza_Actor
		);
		pizza->StopActions();
		pizza->FUN_100382b0();
		m_pizzaVisible = FALSE;
	}

	IslePathActor::Exit();
	GameState()->m_currentArea = LegoGameState::Area::e_skateboard;
	RemoveFromCurrentWorld(*g_isleScript, IsleScript::c_SkateArms_Ctl);
	RemoveFromCurrentWorld(*g_isleScript, IsleScript::c_SkatePizza_Bitmap);
	ControlManager()->Unregister(this);
}

MxLong SkateBoard::HandleClick() {
	Act1State* state = (Act1State*) GameState()->GetState("Act1State");

	if (!FUN_1003ef60() && state->m_unk0x018 != 3) {
		return 1;
	}

	FUN_10015820(TRUE, 0);

	((Isle*) CurrentWorld())
		->SetDestLocation(LegoGameState::Area::e_skateboard);
	TransitionManager()
		->StartTransition(MxTransitionManager::e_mosaic, 50, FALSE, TRUE);

	if (GameState()->GetActorId() != UserActor()->GetActorId()) {
		if (!UserActor()->IsA("SkateBoard")) {
			((IslePathActor*) UserActor())->Exit();
		}
	}

	if (!UserActor()->IsA("SkateBoard")) {
		Enter();
		InvokeAction(
			Extra::ActionType::e_start,
			*g_isleScript,
			IsleScript::c_SkateDashboard,
			NULL
		);
		GetCurrentAction().SetObjectId(-1);
		ControlManager()->Register(this);
	}

	EnableScenePresentation(m_pizzaVisible);

	Vector3 position = m_roi->GetWorldPosition();
	AnimationManager()->FUN_10064670(&position);
	AnimationManager()->FUN_10064740(&position);
	return 1;
}

MxLong SkateBoard::HandleControl(LegoControlManagerNotificationParam& p_param) {
	MxU32 result = 0;

	if (p_param.GetUnknown0x28() == 1 &&
		p_param.GetClickedObjectId() == IsleScript::c_SkateArms_Ctl) {
		Exit();
		GameState()->m_currentArea = LegoGameState::Area::e_unk66;
		result = 1;
	}

	return result;
}

void SkateBoard::EnableScenePresentation(MxBool p_enable) {
	m_act1state = (Act1State*) GameState()->GetState("Act1State");
	if (!m_act1state) {
		m_act1state = (Act1State*) GameState()->CreateState("Act1State");
	}

	MxStillPresenter* presenter =
		(MxStillPresenter*)
			m_world->Find(*g_isleScript, IsleScript::c_SkatePizza_Bitmap);
	if (presenter) {
		presenter->Enable(p_enable);
	} else if (m_pizzaVisible) {
		NotificationManager()->Send(
			this,
			MxNotificationParam(c_notificationType0, NULL)
		);
	}
}

MxLong SkateBoard::HandleNotification0() {
	EnableScenePresentation(m_pizzaVisible);
	return 1;
}

void SkateBoard::ActivateSceneActions() {
	if (m_act1state->m_unk0x018 != 3) {
		PlayMusic(JukeboxScript::c_BeachBlvd_Music);

		if (!m_act1state->m_unk0x022) {
			m_act1state->m_unk0x022 = TRUE;

			MxMatrix mat(UserActor()->GetROI()->GetLocal2World());
			mat.TranslateBy(mat[2][0] * 2.5, mat[2][1] + 0.2, mat[2][2] * 2.5);

			AnimationManager()->FUN_10060dc0(
				IsleScript::c_sns008in_RunAnim,
				&mat,
				TRUE,
				LegoAnimationManager::e_unk0,
				NULL,
				FALSE,
				TRUE,
				TRUE,
				TRUE
			);
		}
	}
}
