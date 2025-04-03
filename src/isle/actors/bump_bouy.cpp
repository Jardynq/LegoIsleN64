#include "bump_bouy.h"

#include "isle.h"
#include "isle_actions.h"
#include "isle_path_actor.h"
#include "gamestate.h"
#include "video_manager.h"
#include "misc.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_notification_param.h"
#include "mx_transition_manager.h"
#include "scripts.h"

#include <assert.h>

BumpBouy::BumpBouy() {
	NotificationManager()->Register(this);
}

BumpBouy::~BumpBouy() {
	NotificationManager()->Unregister(this);
}

MxLong BumpBouy::Notify(MxParam& p_param) {
	MxLong result = 0;
	MxNotificationParam& param = (MxNotificationParam&) p_param;

	IslePathActor* user = (IslePathActor*) UserActor();
	assert(user);

	if (user->IsA("Jetski") && param.GetNotification() == c_notificationClick) {
		VideoManager()->SetRender3D(FALSE);
		user->SetWorldSpeed(0);
		user->Exit();

		Act1State* isleState = (Act1State*) GameState()->GetState("Act1State");
		assert(isleState);
		isleState->m_unk0x018 = 5;

		Isle* isle = (Isle*) FindWorld(*g_isleScript, IsleScript::c__Isle);
		assert(isle);
		isle->SetDestLocation(LegoGameState::e_jetrace);

		TransitionManager()
			->StartTransition(MxTransitionManager::e_mosaic, 50, FALSE, FALSE);
		result = 1;
	}

	return result;
}
