#ifndef MXTHREAD_H
#define MXTHREAD_H

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
	MxBool m_running;

protected:
	MxCore* m_target;
};

#endif // MXTHREAD_H
