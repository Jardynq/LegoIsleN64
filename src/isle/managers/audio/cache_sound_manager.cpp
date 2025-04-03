#include "cache_sound_manager.h"

#include "world.h"
#include "misc.h"

LegoCacheSoundManager::~LegoCacheSoundManager() {
	LegoCacheSound* sound = nullptr;

	while (!m_set.empty()) {
		sound = (*m_set.begin()).GetSound();
		m_set.erase(m_set.begin());
		sound->Stop();
		delete sound;
	}

	while (!m_list.empty()) {
		sound = (*m_list.begin()).GetSound();
		m_list.erase(m_list.begin());
		sound->Stop();
		delete sound;
	}
}

MxResult LegoCacheSoundManager::Tickle() {
	Set100d6b4c::iterator setIter;
	for (setIter = m_set.begin(); setIter != m_set.end(); setIter++) {
		LegoCacheSound* sound = (*setIter).GetSound();
		if (sound->GetIsPlaying()) {
			sound->Tickle();
		}
	}

	List100d6b4c::iterator listIter = m_list.begin();
	while (listIter != m_list.end()) {
		LegoCacheSound* sound = (*listIter).GetSound();

		if (sound->GetIsPlaying()) {
			sound->Tickle();
			listIter++;
		} else {
			sound->Stop();
			m_list.erase(listIter++);
			delete sound;
		}
	}

	return SUCCESS;
}

LegoCacheSound* LegoCacheSoundManager::FindSoundByKey(const char* p_key) {
	char* key = new char[strlen(p_key) + 1];
	strcpy(key, p_key);

	Set100d6b4c::iterator it = m_set.find(LegoCacheSoundEntry(NULL, key));
	if (it != m_set.end()) {
		return (*it).GetSound();
	}

	return NULL;
}

LegoCacheSound* LegoCacheSoundManager::ManageSoundEntry(LegoCacheSound* p_sound
) {
	Set100d6b4c::iterator it = m_set.find(LegoCacheSoundEntry(p_sound));
	if (it != m_set.end()) {
		LegoCacheSound* sound = (*it).GetSound();

		if (sound->GetIsPlaying()) {
			m_list.push_back(LegoCacheSoundEntry(p_sound));
			return p_sound;
		} else {
			delete p_sound;
			return sound;
		}
	}

	m_set.insert(LegoCacheSoundEntry(p_sound));
	LegoWorld* world = CurrentWorld();
	if (world) {
		world->Add(p_sound);
	}

	return p_sound;
}

LegoCacheSound* LegoCacheSoundManager::Play(
	const char* p_key,
	const char* p_name,
	MxBool p_looping
) {
	return Play(FindSoundByKey(p_key), p_name, p_looping);
}

LegoCacheSound* LegoCacheSoundManager::Play(
	LegoCacheSound* p_sound,
	const char* p_name,
	MxBool p_looping
) {
	if (!p_sound) {
		return NULL;
	}

	if (p_sound->GetIsPlaying()) {
		LegoCacheSound* clone = p_sound->Clone();

		if (clone) {
			LegoCacheSound* sound = ManageSoundEntry(clone);
			sound->Play(p_name, p_looping);
			return sound;
		}
	} else {
		p_sound->Play(p_name, p_looping);
		return p_sound;
	}

	return NULL;
}

void LegoCacheSoundManager::Stop(LegoCacheSound*& p_sound) {
	Set100d6b4c::iterator setIter;
	for (setIter = m_set.begin(); setIter != m_set.end(); setIter++) {
		if ((*setIter).GetSound() == p_sound) {
			p_sound->Stop();
			return;
		}
	}

	List100d6b4c::iterator listIter;
	for (listIter = m_list.begin();; listIter++) {
		if (listIter == m_list.end()) {
			return;
		}

		LegoCacheSound* sound = (*listIter).GetSound();
		if (sound == p_sound) {
			p_sound->Stop();
			return;
		}
	}
}

void LegoCacheSoundManager::Destroy(LegoCacheSound*& p_sound) {
	Set100d6b4c::iterator setIter;
	for (setIter = m_set.begin(); setIter != m_set.end(); setIter++) {
		if ((*setIter).GetSound() == p_sound) {
			p_sound->Stop();

			delete p_sound;
			m_set.erase(setIter);
			return;
		}
	}

	List100d6b4c::iterator listIter;
	for (listIter = m_list.begin();; listIter++) {
		if (listIter == m_list.end()) {
			return;
		}

		LegoCacheSound* sound = (*listIter).GetSound();
		if (sound == p_sound) {
			p_sound->Stop();

			delete sound;
			m_list.erase(listIter);
			return;
		}
	}
}
