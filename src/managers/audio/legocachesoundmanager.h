#ifndef LEGOCACHESOUNDMANAGER_H
#define LEGOCACHESOUNDMANAGER_H

#include "legocachsound.h"

struct LegoCacheSoundEntry {
	LegoCacheSoundEntry() : m_sound(NULL), m_name(NULL) {}
	LegoCacheSoundEntry(LegoCacheSound* p_sound, const char* p_name)
		: m_sound(p_sound), m_name(p_name) {}
	LegoCacheSoundEntry(LegoCacheSound* p_sound)
		: m_sound(p_sound), m_name(p_sound->GetFileName().GetData()) {}

	~LegoCacheSoundEntry() {
		if (m_sound == NULL && m_name != NULL) {
			delete[] const_cast<char*>(m_name);
		}
	}

	bool operator==(const LegoCacheSoundEntry&) const { return 0; }
	bool operator<(const LegoCacheSoundEntry&) const { return 0; }

	LegoCacheSound* GetSound() const { return m_sound; }
	const char* GetName() const { return m_name; }

	friend struct Set100d6b4cComparator;

private:
	LegoCacheSound* m_sound;
	const char* m_name;
};

struct Set100d6b4cComparator {
	bool operator()(
		const LegoCacheSoundEntry& p_a,
		const LegoCacheSoundEntry& p_b
	) const {
		return strcmpi(p_a.m_name, p_b.m_name) > 0;
	}
};

typedef set<LegoCacheSoundEntry, Set100d6b4cComparator> Set100d6b4c;
typedef list<LegoCacheSoundEntry> List100d6b4c;

class LegoCacheSoundManager {
public:
	LegoCacheSoundManager() {}
	~LegoCacheSoundManager();

	MxResult Tickle();

	LegoCacheSound* FindSoundByKey(const char* p_key);
	LegoCacheSound* ManageSoundEntry(LegoCacheSound* p_sound);
	LegoCacheSound*
	Play(const char* p_key, const char* p_name, MxBool p_looping);
	LegoCacheSound*
	Play(LegoCacheSound* p_sound, const char* p_name, MxBool p_looping);
	void Stop(LegoCacheSound*& p_sound);
	void Destroy(LegoCacheSound*& p_sound);

private:
	Set100d6b4c m_set;
	List100d6b4c m_list;
};

#endif // LEGOCACHESOUNDMANAGER_H
