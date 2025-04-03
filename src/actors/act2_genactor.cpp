#include "act2_genactor.h"

#include "cache_sound_manager.h"
#include "sound_manager.h"
#include "misc.h"
#include "mx_misc.h"
#include "mx_timer.h"
#include "roi.h"

MxLong Act2GenActor::g_lastHitActorTime = 0;

MxResult Act2GenActor::HitActor(LegoPathActor* p_actor, MxBool) {
	MxLong time = Timer()->GetTime();
	MxLong diff = time - g_lastHitActorTime;

	if (strcmp(p_actor->GetROI()->GetName(), "pepper")) {
		return SUCCESS;
	}

	g_lastHitActorTime = time;
	if (diff > 1000) {
		SoundManager()->GetCacheSoundManager()->Play("hitactor", NULL, FALSE);
	}

	return SUCCESS;
}
