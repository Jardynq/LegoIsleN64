
#include "mxsemaphore.h"

MxSemaphore::MxSemaphore() {
	m_hSemaphore = NULL;
}

MxResult MxSemaphore::Init(MxU32 p_initialCount, MxU32 p_maxCount) {
	MxResult result = FAILURE;

	if ((m_hSemaphore =
			 CreateSemaphoreA(NULL, p_initialCount, p_maxCount, NULL))) {
		result = SUCCESS;
	}

	return result;
}

void MxSemaphore::Wait(MxU32 p_timeoutMS) {
	WaitForSingleObject(m_hSemaphore, p_timeoutMS);
}

void MxSemaphore::Release(MxU32 p_releaseCount) {
	ReleaseSemaphore(m_hSemaphore, p_releaseCount, NULL);
}
