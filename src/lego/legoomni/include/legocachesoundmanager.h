#ifndef LEGOCACHESOUNDMANAGER_H
#define LEGOCACHESOUNDMANAGER_H

#include "legocachsound.h"

#pragma warning(disable : 4237)

struct LegoCacheSoundEntry {
	LegoCacheSoundEntry() : m_sound(NULL), m_name(NULL) {}
	LegoCacheSoundEntry(LegoCacheSound* p_sound, const char* p_name)
		: m_sound(p_sound), m_name(p_name) {}
	LegoCacheSoundEntry(LegoCacheSound* p_sound)
		: m_sound(p_sound), m_name(p_sound->GetUnknown0x48().GetData()) {}

	~LegoCacheSoundEntry() {
		if (m_sound == NULL && m_name != NULL) {
			delete[] const_cast<char*>(m_name);
		}
	}

	bool operator==(LegoCacheSoundEntry) const { return 0; }
	bool operator<(LegoCacheSoundEntry) const { return 0; }

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

	virtual MxResult Tickle();

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

// TODO: Function names subject to change.

// clang-format off

// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::~_Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::iterator::_Inc


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::erase


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Erase


// list<LegoCacheSoundEntry,allocator<LegoCacheSoundEntry> >::~list<LegoCacheSoundEntry,allocator<LegoCacheSoundEntry> >


// set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::~set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >


// Set<LegoCacheSoundEntry,Set100d6b4cComparator>::~Set<LegoCacheSoundEntry,Set100d6b4cComparator>


// List<LegoCacheSoundEntry>::~List<LegoCacheSoundEntry>


// list<LegoCacheSoundEntry,allocator<LegoCacheSoundEntry> >::_Buynode


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::insert


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::iterator::_Dec


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Buynode


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Insert


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Lrotate


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Rrotate


// _Tree<LegoCacheSoundEntry,LegoCacheSoundEntry,set<LegoCacheSoundEntry,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Kfn,Set100d6b4cComparator,allocator<LegoCacheSoundEntry> >::_Nil
// clang-format on

#endif // LEGOCACHESOUNDMANAGER_H
