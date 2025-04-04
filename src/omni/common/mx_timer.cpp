#include "mx_timer.h"

#include "timer.h"

MxLong MxTimer::g_lastTimeCalculated = 0;
MxLong MxTimer::g_lastTimeTimerStarted = 0;

MxTimer::MxTimer() {
	m_isRunning = FALSE;
	m_startTime = TIMER_MICROS(timer_ticks());
	InitLastTimeCalculated();
}

MxLong MxTimer::GetRealTime() {
	MxTimer::g_lastTimeCalculated = TIMER_MICROS(timer_ticks());
	return MxTimer::g_lastTimeCalculated - m_startTime;
}

void MxTimer::Start() {
	g_lastTimeTimerStarted = TIMER_MICROS(timer_ticks());
	m_isRunning = TRUE;
}

void MxTimer::Stop() {
	MxLong elapsed = TIMER_MICROS(timer_ticks());
	MxLong startTime = elapsed - MxTimer::g_lastTimeTimerStarted;
	m_isRunning = FALSE;
	// this feels very stupid but it's what the assembly does
	m_startTime = m_startTime + startTime - 5;
}
