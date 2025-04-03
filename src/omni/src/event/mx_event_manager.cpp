#include "mx_event_manager.h"

#include "mxcriticalsection.h"
#include "mx_misc.h"
#include "mx_tickle_manager.h"
#include "mxticklethread.h"

MxEventManager::MxEventManager() {
	Init();
}

MxEventManager::~MxEventManager() {
	Destroy(TRUE);
}

void MxEventManager::Init() {
	// This is intentionally left blank
}

void MxEventManager::Destroy(MxBool p_fromDestructor) {
	if (m_thread != NULL) {
		m_thread->Terminate();
		delete m_thread;
	} else {
		TickleManager()->UnregisterClient(this);
	}

	if (!p_fromDestructor) {
		MxMediaManager::Destroy();
	}
}

MxResult MxEventManager::Create(MxU32 p_frequencyMS, MxBool p_createThread) {
	MxResult status = FAILURE;
	MxBool locked = FALSE;

	MxResult result = MxMediaManager::Create();
	if (result == SUCCESS) {
		if (p_createThread) {
			this->m_criticalSection.Enter();
			locked = TRUE;
			this->m_thread = new MxTickleThread(this, p_frequencyMS);

			if (!this->m_thread || this->m_thread->Start(0, 0) != SUCCESS) {
				goto done;
			}
		} else {
			TickleManager()->RegisterClient(this, p_frequencyMS);
		}

		status = SUCCESS;
	}

done:
	if (status != SUCCESS) {
		Destroy();
	}

	if (locked) {
		this->m_criticalSection.Leave();
	}

	return status;
}

void MxEventManager::Destroy() {
	Destroy(FALSE);
}
