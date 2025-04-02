#ifndef MXSEMAPHORE_H
#define MXSEMAPHORE_H

class MxSemaphore {
public:
	MxSemaphore();

	~MxSemaphore() {}

	virtual MxResult Init(MxU32 p_initialCount, MxU32 p_maxCount);

	void Wait(MxU32 p_timeoutMS);
	void Release(MxU32 p_releaseCount);
};

#endif // MXSEMAPHORE_H
