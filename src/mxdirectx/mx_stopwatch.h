#ifndef _MxStopWatch_h
#define _MxStopWatch_h

#include "assert.h"
#include "timer.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//
// MxStopWatch
//
// NOTE:	MxStopWatch measures elapsed (wall clock) time.
//

class MxStopWatch {
public:
	MxStopWatch();
	~MxStopWatch() {}

	void Start();
	void Stop();
	void Reset();

	double ElapsedSeconds() const;

private:
	u64 m_startTick;
	double m_elapsedSeconds;
};

inline MxStopWatch::MxStopWatch() {
	Reset();
}

inline void MxStopWatch::Start() {
	m_startTick = timer_ticks();
}

inline void MxStopWatch::Stop() {
	u64 endTick = timer_ticks();
	m_elapsedSeconds +=
		(double) TIMER_MICROS(endTick - m_startTick) * 1000000.0;
}

inline void MxStopWatch::Reset() {
	m_startTick = 0;
	m_elapsedSeconds = 0;
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
