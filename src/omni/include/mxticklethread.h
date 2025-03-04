#ifndef MXTICKLETHREAD_H
#define MXTICKLETHREAD_H

#include "mxthread.h"

class MxTickleThread : public MxThread {
public:
	MxTickleThread(MxCore* p_target, MxS32 p_frequencyMS);

	MxResult Run() override;

	// MxTickleThread::`scalar deleting destructor'

private:
	MxS32 m_frequencyMS;
};

#endif // MXTICKLETHREAD_H
