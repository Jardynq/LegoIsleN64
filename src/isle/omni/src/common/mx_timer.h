#ifndef MXTIMER_H
#define MXTIMER_H

#include "mx_core.h"

class MxTimer : public MxCore {
public:
	MxTimer();

	void Start();
	void Stop();

	MxLong GetRealTime();

	void InitLastTimeCalculated() { g_lastTimeCalculated = m_startTime; }

	MxLong GetTime() {
		// Note that the BETA10 implementation differs - it only consists of the
		// second branch of this `if` call
		if (m_isRunning) {
			return g_lastTimeTimerStarted;
		} else {
			return g_lastTimeCalculated - m_startTime;
		}
	}

	// MxTimer::`scalar deleting destructor'

private:
	MxLong m_startTime;
	MxBool m_isRunning;
	static MxLong g_lastTimeCalculated;
	static MxLong g_lastTimeTimerStarted;
};

// MxTimer::~MxTimer

#endif // MXTIMER_H
