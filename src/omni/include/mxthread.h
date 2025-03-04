#ifndef MXTHREAD_H
#define MXTHREAD_H

#include "mxsemaphore.h"

class MxCore;

class MxThread {
public:
	// Note: Comes before virtual destructor
	virtual MxResult Run();

	MxResult Start(MxS32 p_stack, MxS32 p_flag);

	void Terminate();
	void Sleep(MxS32 p_milliseconds);

	MxBool IsRunning() { return m_running; }

	// MxThread::`scalar deleting destructor'

protected:
	MxThread();

public:
	virtual ~MxThread();

private:
	static unsigned __attribute__((stdcall)) ThreadProc(void* p_thread);

	MxULong m_hThread;
	MxU32 m_threadId;
	MxBool m_running;
	MxSemaphore m_semaphore;

protected:
	MxCore* m_target;
};

#endif // MXTHREAD_H
