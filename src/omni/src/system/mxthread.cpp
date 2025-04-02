#include "mxthread.h"

MxThread::MxThread() {
	m_running = TRUE;
}

MxThread::~MxThread() {
}

MxResult MxThread::Start(MxS32 p_stack, MxS32 p_flag) {
	(void) p_stack;
	(void) p_flag;
	return SUCCESS;
}

void MxThread::Sleep(MxS32 p_milliseconds) {
	wait_ms((u32) p_milliseconds);
}

void MxThread::Terminate() {
	m_running = FALSE;
}

MxResult MxThread::Run() {
	return SUCCESS;
}
