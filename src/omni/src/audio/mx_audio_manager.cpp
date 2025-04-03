#include "mx_audio_manager.h"

MxS32 MxAudioManager::g_count = 0;

MxAudioManager::MxAudioManager() {
	Init();
}

MxAudioManager::~MxAudioManager() {
	Destroy(TRUE);
}

void MxAudioManager::Init() {
	m_volume = 100;
}

void MxAudioManager::Destroy(MxBool p_fromDestructor) {
	m_criticalSection.Enter();
	g_count--;
	Init();
	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		MxMediaManager::Destroy();
	}
}

MxResult MxAudioManager::Create() {
	MxResult result = FAILURE;
	MxBool success = FALSE;

	if (MxMediaManager::Create() == SUCCESS) {
		m_criticalSection.Enter();
		success = TRUE;
		result = SUCCESS;
		g_count++;
	}

	if (result) {
		Destroy();
	}

	if (success) {
		m_criticalSection.Leave();
	}

	return result;
}

void MxAudioManager::Destroy() {
	Destroy(FALSE);
}

void MxAudioManager::SetVolume(MxS32 p_volume) {
	m_criticalSection.Enter();
	m_volume = p_volume;
	m_criticalSection.Leave();
}
