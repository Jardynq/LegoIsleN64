#pragma once

#include "path_actor.h"

class Act2GenActor : public LegoPathActor {
	MxResult HitActor(LegoPathActor* p_actor, MxBool) override;

	// Act2GenActor::`scalar deleting destructor'

private:
	static MxLong g_lastHitActorTime;
};

