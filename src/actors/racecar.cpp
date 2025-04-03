#include "racecar.h"

#include "isle.h"
#include "isle_actions.h"
#include "control_manager.h"
#include "utils.h"
#include "world.h"
#include "misc.h"
#include "mx_transition_manager.h"

RaceCar::RaceCar() {
	m_maxLinearVel = 40.0;
}

RaceCar::~RaceCar() {
	ControlManager()->Unregister(this);
	Exit();
}

MxResult RaceCar::Create(MxDSAction& p_dsAction) {
	MxResult result = IslePathActor::Create(p_dsAction);
	m_world = CurrentWorld();

	if (m_world) {
		m_world->Add(this);
	}

	ControlManager()->Register(this);
	return result;
}

MxLong RaceCar::HandleClick() {
	if (!FUN_1003ef60()) {
		return 1;
	}

	Isle* isle = (Isle*) FindWorld(*g_isleScript, IsleScript::c__Isle);
	isle->SetDestLocation(LegoGameState::Area::e_carrace);
	TransitionManager()
		->StartTransition(MxTransitionManager::e_mosaic, 50, FALSE, FALSE);
	return 1;
}
