#ifndef MXSEMAPHORE_H
#define MXSEMAPHORE_H

#include <windows.h>

class MxSemaphore {
public:
	MxSemaphore();

	~MxSemaphore() { CloseHandle(m_hSemaphore); }

	virtual MxResult Init(MxU32 p_initialCount, MxU32 p_maxCount);

	void Wait(MxU32 p_timeoutMS);
	void Release(MxU32 p_releaseCount);

private:
	HANDLE m_hSemaphore;
};

#endif // MXSEMAPHORE_H
