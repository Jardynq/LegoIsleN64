#include "mxautolock.h"

#include "mxcriticalsection.h"

MxAutoLock::MxAutoLock(MxCriticalSection* p_criticalSection) {
	m_criticalSection = p_criticalSection;

	if (m_criticalSection != NULL) {
		m_criticalSection->Enter();
	}
}

MxAutoLock::~MxAutoLock() {
	if (m_criticalSection != NULL) {
		m_criticalSection->Leave();
	}
}
