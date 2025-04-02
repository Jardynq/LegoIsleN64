
#include "mxsemaphore.h"

MxSemaphore::MxSemaphore() {
}

MxResult MxSemaphore::Init(MxU32 p_initialCount, MxU32 p_maxCount) {
	(void) p_initialCount;
	(void) p_maxCount;
	return SUCCESS;
}

void MxSemaphore::Wait(MxU32 p_timeoutMS) {
	(void) p_timeoutMS;
}

void MxSemaphore::Release(MxU32 p_releaseCount) {
	(void) p_releaseCount;
}
