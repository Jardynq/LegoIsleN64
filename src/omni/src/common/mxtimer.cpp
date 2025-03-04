#include "mxtimer.h"

#include <windows.h>

MxLong MxTimer::g_lastTimeCalculated = 0;

MxLong MxTimer::g_lastTimeTimerStarted = 0;

MxTimer::MxTimer() {
	m_isRunning = FALSE;
	m_startTime = timeGetTime();
	InitLastTimeCalculated();
}

MxLong MxTimer::GetRealTime() {
	MxTimer::g_lastTimeCalculated = timeGetTime();
	return MxTimer::g_lastTimeCalculated - m_startTime;
}

void MxTimer::Start() {
	g_lastTimeTimerStarted = GetRealTime();
	m_isRunning = TRUE;
}

void MxTimer::Stop() {
	MxLong elapsed = GetRealTime();
	MxLong startTime = elapsed - MxTimer::g_lastTimeTimerStarted;
	m_isRunning = FALSE;
	// this feels very stupid but it's what the assembly does
	m_startTime = m_startTime + startTime - 5;
}
