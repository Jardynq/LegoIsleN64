#include "mx_music_manager.h"

#include "mx_misc.h"
#include "mx_tickle_manager.h"

MxMusicManager::MxMusicManager() {
	Init();
}

MxMusicManager::~MxMusicManager() {
	Destroy(TRUE);
}

void MxMusicManager::Init() {
	m_multiplier = 100;
	InitData();
}

void MxMusicManager::InitData() {
	m_midiInitialized = FALSE;
	m_bufferSize = 0;
	m_bufferCurrentSize = 0;
	m_bufferOffset = 0;
	m_bufferCurrentOffset = 0;
	m_loopCount = 0;
}

void MxMusicManager::Destroy(MxBool p_fromDestructor) {
	TickleManager()->UnregisterClient(this);

	m_criticalSection.Enter();
	DeinitializeMIDI();
	Init();
	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		MxAudioManager::Destroy();
	}
}

MxResult MxMusicManager::ResetStream() {
	log_unimpl();
	return SUCCESS;
}

void MxMusicManager::ResetBuffer() {
	m_bufferCurrentOffset = m_bufferOffset;
	m_bufferCurrentSize = m_bufferSize;
}

void MxMusicManager::SetMIDIVolume() {
	log_unimpl();
}


MxResult MxMusicManager::Create(MxU32 p_frequencyMS) {
	MxResult status = FAILURE;

	if (MxAudioManager::Create() == SUCCESS) {
		TickleManager()->RegisterClient(this, p_frequencyMS);
		status = SUCCESS;
	}

	if (status != SUCCESS) {
		Destroy();
	}

	return status;
}

void MxMusicManager::Destroy() {
	Destroy(FALSE);
}

void MxMusicManager::SetVolume(MxS32 p_volume) {
	MxAudioManager::SetVolume(p_volume);
	m_criticalSection.Enter();
	SetMIDIVolume();
	m_criticalSection.Leave();
}

void MxMusicManager::SetMultiplier(MxS32 p_multiplier) {
	m_criticalSection.Enter();
	m_multiplier = p_multiplier;
	SetMIDIVolume();
	m_criticalSection.Leave();
}

MxS32 MxMusicManager::CalculateVolume(MxS32 p_volume) {
	MxS32 result = (p_volume * 0xffff) / 100;
	return (result << 0x10) | result;
}

MxResult MxMusicManager::InitializeMIDI(MxU8* p_data, MxS32 p_loopCount) {
	(void)p_data;
	(void)p_loopCount;
	log_unimpl();
	return SUCCESS;
}

void MxMusicManager::DeinitializeMIDI() {
	log_unimpl();
}
