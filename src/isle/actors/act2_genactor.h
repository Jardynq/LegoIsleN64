#ifndef ACT2GENACTOR_H
#define ACT2GENACTOR_H

#include "path_actor.h"

class Act2GenActor : public LegoPathActor {
	MxResult HitActor(LegoPathActor* p_actor, MxBool) override;

	// Act2GenActor::`scalar deleting destructor'

private:
	static MxLong g_lastHitActorTime;
};

#endif // ACT2GENACTOR_H
