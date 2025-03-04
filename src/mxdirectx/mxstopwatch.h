#ifndef _MxStopWatch_h
#define _MxStopWatch_h

#include "assert.h"

#include <limits.h> // ULONG_MAX
#include <math.h>
#include <windows.h>

//////////////////////////////////////////////////////////////////////////////
//
// MxStopWatch
//
// NOTE:	MxStopWatch measures elapsed (wall clock) time.
//

#define HUGE_VAL_IMMEDIATE 1.7976931348623157e+308

class MxStopWatch {
public:
	MxStopWatch();
	~MxStopWatch() {}

	void Start();
	void Stop();
	void Reset();

	double ElapsedSeconds() const;

protected:
	unsigned int TicksPerSeconds() const;

private:
	LARGE_INTEGER
	m_startTick; // ??? when we provide LARGE_INTEGER arithmetic, use a
	//     LARGE_INTEGER m_elapsedTicks rather than m_elapsedSeconds
	double m_elapsedSeconds;
	unsigned int m_ticksPerSeconds;
};

inline MxStopWatch::MxStopWatch() : m_ticksPerSeconds(TicksPerSeconds()) {
	Reset();
}

inline void MxStopWatch::Start() {
	QueryPerformanceCounter(&m_startTick);
}

inline void MxStopWatch::Stop() {
	LARGE_INTEGER endTick;
	BOOL result = 0;

	result = QueryPerformanceCounter(&endTick);
	assert(result);

	if (endTick.HighPart != m_startTick.HighPart) {
		// LARGE_INTEGER arithmetic not yet provided
		m_elapsedSeconds = HUGE_VAL_IMMEDIATE;
	} else {
		m_elapsedSeconds +=
			((endTick.LowPart - m_startTick.LowPart) /
			 (double) m_ticksPerSeconds);
	}
}

inline void MxStopWatch::Reset() {
	m_startTick.LowPart = 0;
	m_startTick.HighPart = 0;
	m_elapsedSeconds = 0;
}

inline unsigned int MxStopWatch::TicksPerSeconds() const {
	LARGE_INTEGER ticksPerSeconds;
	BOOL result = 0;

	result = QueryPerformanceFrequency(&ticksPerSeconds);
	assert(result);

	if (ticksPerSeconds.HighPart) {
		// LARGE_INTEGER arithmetic not yet provided

		// timer is too fast (faster than 32bits/s, i.e. faster than 4GHz)
		return ULONG_MAX;
	} else {
		return ticksPerSeconds.LowPart;
	}
}

inline double MxStopWatch::ElapsedSeconds() const {
	return m_elapsedSeconds;
}

// MxStopWatch::~MxStopWatch

//////////////////////////////////////////////////////////////////////////////
//
// MxFrequencyMeter
//

class MxFrequencyMeter {
public:
	MxFrequencyMeter();

	void StartOperation();
	void EndOperation();
	double Frequency() const;
	void Reset();

	unsigned int OperationCount() const;
	double ElapsedSeconds() const;

	void IncreaseOperationCount(unsigned int);

private:
	unsigned int m_operationCount;
	MxStopWatch m_stopWatch;
};

//////////////////////////////////////////////////////////////////////////////
//
// MxFrequencyMeter implementation
//

inline MxFrequencyMeter::MxFrequencyMeter() : m_operationCount(0) {
}

inline void MxFrequencyMeter::StartOperation() {
	m_stopWatch.Start();
}

inline void MxFrequencyMeter::EndOperation() {
	m_stopWatch.Stop();
	m_operationCount++;
}

inline double MxFrequencyMeter::Frequency() const {
	double elapsedSeconds = m_stopWatch.ElapsedSeconds();

	if (elapsedSeconds > 0) {
		return m_operationCount / elapsedSeconds;
	} else {
		if (m_operationCount) {
			// operations performed - no time elapsed
			return HUGE_VAL;
		} else {
			// no operations performed - no time elapsed
			return 0;
		}
	}
}

inline void MxFrequencyMeter::Reset() {
	m_stopWatch.Reset();
	m_operationCount = 0;
}

inline unsigned int MxFrequencyMeter::OperationCount() const {
	return m_operationCount;
}

inline void MxFrequencyMeter::IncreaseOperationCount(unsigned int delta) {
	m_operationCount += delta;
}

inline double MxFrequencyMeter::ElapsedSeconds() const {
	return m_stopWatch.ElapsedSeconds();
}

// MxFrequencyMeter::~MxFrequencyMeter

#endif /* _MxStopWatch_h */
