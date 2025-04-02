#include "legosoundmanager.h"

#include "legocachesoundmanager.h"
#include "manager.h"
#include "mxaudiopresenter.h"
#include "mxdsaction.h"
#include "mxwavepresenter.h"

LegoSoundManager::LegoSoundManager() {
	Init();
}

LegoSoundManager::~LegoSoundManager() {
	Destroy();
}

void LegoSoundManager::Init() {
	m_cacheSoundManager = NULL;
}

void LegoSoundManager::Destroy() {
	Manager::Destroy();
	delete m_cacheSoundManager;
	Init();
}

MxResult LegoSoundManager::Create(MxU32 p_frequencyMS) {
	MxResult result = FAILURE;

	if (Manager::Create(p_frequencyMS) == SUCCESS) {
		m_cacheSoundManager = new LegoCacheSoundManager();
		result = SUCCESS;
	}

	if (result != SUCCESS) {
		Destroy();
	}

	return result;
}

MxResult LegoSoundManager::Tickle() {
	Manager::Tickle();
	return m_cacheSoundManager->Tickle();
}

void LegoSoundManager::UpdateListener(
	const float* p_position,
	const float* p_direction,
	const float* p_up,
	const float* p_velocity
) {
	(void)p_position;
	(void)p_direction;
	(void)p_up;
	(void)p_velocity;
	log_unimpl();
}


MxS32 LegoSoundManager::GetVolume() {
	return m_volume;
}

void LegoSoundManager::SetVolume(MxS32 p_volume) {
	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(m_presenters);

	while (cursor.Next(presenter)) {
		((MxAudioPresenter*) presenter)->SetVolume(p_volume);
	}
}

MxPresenter* LegoSoundManager::FUN_100aebd0(const MxAtomId& p_atomId, MxU32 p_objectId) {
	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(m_presenters);

	while (cursor.Next(presenter)) {
		if (presenter->GetAction()->GetAtomId().GetInternal() ==
				p_atomId.GetInternal() &&
			presenter->GetAction()->GetObjectId() == p_objectId) {
			return presenter;
		}
	}

	return NULL;
}

void LegoSoundManager::Pause() {
	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(m_presenters);

	while (cursor.Next(presenter)) {
		if (presenter->IsA("MxWavePresenter")) {
			((MxWavePresenter*) presenter)->Pause();
		}
	}
}

void LegoSoundManager::Resume() {
	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(m_presenters);

	while (cursor.Next(presenter)) {
		if (presenter->IsA("MxWavePresenter")) {
			((MxWavePresenter*) presenter)->Resume();
		}
	}
}
