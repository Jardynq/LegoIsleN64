#pragma once

#include "mx_core.h"

class MxTimer : public MxCore {
public:
	MxTimer();

	void Start();
	void Stop();

	MxLong GetRealTime();

	void InitLastTimeCalculated() { g_lastTimeCalculated = m_startTime; }

	MxLong GetTime() {
		if (m_isRunning) {
			return g_lastTimeTimerStarted;
		} else {
			return g_lastTimeCalculated - m_startTime;
		}
	}

private:
	MxLong m_startTime;
	MxBool m_isRunning;
	static MxLong g_lastTimeCalculated;
	static MxLong g_lastTimeTimerStarted;
};
