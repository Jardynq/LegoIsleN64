#include "radio.h"

#include "isle_actions.h"
#include "jukebox_actions.h"
#include "control_manager.h"
#include "gamestate.h"
#include "world.h"
#include "misc.h"
#include "mx_action_notification_param.h"
#include "mx_background_audio_manager.h"
#include "mx_control_presenter.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_timer.h"
#include "scripts.h"

JukeboxScript::Script g_unk0x100f3218[] = {
	JukeboxScript::c_sns002ra_Audio,
	JukeboxScript::c_sns001ja_Audio,
	JukeboxScript::c_snsc01js_Audio,
	JukeboxScript::c_snsb01js_Audio,
	JukeboxScript::c_snsa01js_Audio,
	JukeboxScript::c_sns009ra_Audio};

JukeboxScript::Script g_unk0x100f3230[] = {
	JukeboxScript::c_ham035ra_Audio,
	JukeboxScript::c_ham039ra_Audio,
	JukeboxScript::c_sns005ra_Audio,
	JukeboxScript::c_sns078pa_Audio,
	JukeboxScript::c_ham036ra_Audio,
	JukeboxScript::c_sns006ra_Audio,
	JukeboxScript::c_sns013ra_Audio,
	JukeboxScript::c_sns004ra_Audio,
	JukeboxScript::c_sns079pa_Audio,
	JukeboxScript::c_sns007ra_Audio,
	JukeboxScript::c_sns008ra_Audio,
	JukeboxScript::c_hpz037ma_Audio,
	JukeboxScript::c_sns003ra_Audio,
	JukeboxScript::c_sns010ra_Audio,
};

JukeboxScript::Script g_unk0x100f3268[] = {
	JukeboxScript::c_CentralRoads_Music,
	JukeboxScript::c_BeachBlvd_Music,
	JukeboxScript::c_ResidentalArea_Music,
	JukeboxScript::c_Radio1_Music,
	JukeboxScript::c_Radio2_Music,
	JukeboxScript::c_Radio3_Music,
	JukeboxScript::c_Radio4_Music,
	JukeboxScript::c_Radio5_Music,
	JukeboxScript::c_Radio6_Music,
};

Radio::Radio() {
	NotificationManager()->Register(this);
	ControlManager()->Register(this);

	m_unk0x0c = TRUE;
	CreateState();
}

Radio::~Radio() {
	if (m_state->IsActive()) {
		BackgroundAudioManager()->Stop();
		m_state->SetActive(FALSE);
	}

	ControlManager()->Unregister(this);
	NotificationManager()->Unregister(this);
}

MxLong Radio::Notify(MxParam& p_param) {
	MxLong result = 0;

	if (m_unk0x0c) {
		MxNotificationParam& param = (MxNotificationParam&) p_param;
		switch (param.GetNotification()) {
		case c_notificationEndAction:
			result = HandleEndAction((MxEndActionNotificationParam&) p_param);
			break;
		case c_notificationControl:
			result =
				HandleControl((LegoControlManagerNotificationParam&) p_param);
			break;
		}
	}

	return result;
}

void Radio::Play() {
	if (!m_state->IsActive()) {
		CurrentWorld();

		MxDSAction action;
		action.SetObjectId(m_state->FUN_1002d090());
		action.SetAtomId(*g_jukeboxScript);
		action.SetLoopCount(1);

		m_audioEnabled = BackgroundAudioManager()->GetEnabled();
		if (!m_audioEnabled) {
			BackgroundAudioManager()->Enable(TRUE);
		}

		BackgroundAudioManager()
			->PlayMusic(action, 3, MxPresenter::e_repeating);
		m_state->SetActive(TRUE);
	}
}

void Radio::Stop() {
	if (m_state->IsActive()) {
		LegoWorld* world = CurrentWorld();

		MxControlPresenter* presenter =
			(MxControlPresenter*)
				world->Find(world->GetAtomId(), IsleScript::c_Radio_Ctl);

		if (presenter) {
			presenter->VTable0x6c(0);
		}

		BackgroundAudioManager()->Stop();
		BackgroundAudioManager()->Enable(m_audioEnabled);
		m_state->SetActive(FALSE);
	}
}

MxLong Radio::HandleControl(LegoControlManagerNotificationParam& p_param) {
	MxDSAction action; // Unused
	MxS32 objectId = p_param.GetClickedObjectId();

	if (objectId == IsleScript::c_Radio_Ctl) {
		if (m_state->IsActive()) {
			Stop();
		} else {
			Play();
		}

		if (CurrentWorld()) {
			MxNotificationParam param(c_notificationType0, this);
			CurrentWorld()->Notify(param);
		}

		return 1;
	}

	return 0;
}

MxLong Radio::HandleEndAction(MxEndActionNotificationParam& p_param) {
	if (m_state->IsActive() && m_state->FUN_1002d0c0(
								   p_param.GetAction()->GetAtomId(),
								   p_param.GetAction()->GetObjectId()
							   )) {

		MxDSAction action;
		action.SetAtomId(*g_jukeboxScript);
		action.SetObjectId(m_state->FUN_1002d090());
		action.SetLoopCount(1);

		BackgroundAudioManager()
			->PlayMusic(action, 3, MxPresenter::e_repeating);
		return 1;
	}

	return 0;
}

void Radio::Initialize(MxBool p_und) {
	if (m_unk0x0c != p_und) {
		m_unk0x0c = p_und;
		CreateState();
	}
}

void Radio::CreateState() {
	LegoGameState* gameState = GameState();
	RadioState* state = (RadioState*) gameState->GetState("RadioState");
	if (state == NULL) {
		state = (RadioState*) gameState->CreateState("RadioState");
	}

	m_state = state;
}

RadioState::RadioState() {
	srand(Timer()->GetTime());

	MxS32 random = rand();
	m_unk0x2c = random % 3;

	m_unk0x08[0] = Playlist(
		(MxU32*) g_unk0x100f3218,
		sizeOfArray(g_unk0x100f3218),
		Playlist::e_loop
	);
	m_unk0x08[0].m_nextIndex = (rand() % sizeOfArray(g_unk0x100f3218));

	m_unk0x08[1] = Playlist(
		(MxU32*) g_unk0x100f3230,
		sizeOfArray(g_unk0x100f3230),
		Playlist::e_loop
	);
	m_unk0x08[1].m_nextIndex = (rand() % sizeOfArray(g_unk0x100f3230));

	m_unk0x08[2] = Playlist(
		(MxU32*) g_unk0x100f3268,
		sizeOfArray(g_unk0x100f3268),
		Playlist::e_loop
	);
	m_unk0x08[2].m_nextIndex = (rand() % sizeOfArray(g_unk0x100f3268));

	m_active = FALSE;
}

MxU32 RadioState::FUN_1002d090() {
	if (m_unk0x2c == 2) {
		m_unk0x2c = 0;
	} else {
		m_unk0x2c++;
	}

	return m_unk0x08[m_unk0x2c].Next();
}

MxBool RadioState::FUN_1002d0c0(const MxAtomId& p_atom, MxU32 p_objectId) {
	if (*g_jukeboxScript == p_atom) {
		for (MxS16 i = 0; i < 3; i++) {
			if (m_unk0x08[i].Contains(p_objectId)) {
				return TRUE;
			}
		}
	}

	return FALSE;
}
