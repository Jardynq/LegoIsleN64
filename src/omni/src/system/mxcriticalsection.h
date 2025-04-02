#ifndef MXCRITICALSECTION_H
#define MXCRITICALSECTION_H

#include <libdragon.h>

class MxCriticalSection {
public:
	MxCriticalSection();
	~MxCriticalSection();

	static void SetDoMutex();

	void Enter();
	void Leave();
};

#endif // MXCRITICALSECTION_H
