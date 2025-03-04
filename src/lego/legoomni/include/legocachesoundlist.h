#ifndef LEGOCACHESOUNDLIST_H
#define LEGOCACHESOUNDLIST_H

#include "legocachsound.h"
#include "mxlist.h"

// class MxCollection<LegoCacheSound *>

// class MxList<LegoCacheSound *>

// class MxPtrList<LegoCacheSound>

class LegoCacheSoundList : public MxPtrList<LegoCacheSound> {
public:
	LegoCacheSoundList(MxBool p_ownership = FALSE)
		: MxPtrList<LegoCacheSound>(p_ownership) {}

	MxS8 Compare(LegoCacheSound* p_a, LegoCacheSound* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}
};

// class MxListCursor<LegoCacheSound *>

// class MxPtrListCursor<LegoCacheSound>

class LegoCacheSoundListCursor : public MxPtrListCursor<LegoCacheSound> {
public:
	LegoCacheSoundListCursor(LegoCacheSoundList* p_list)
		: MxPtrListCursor<LegoCacheSound>(p_list) {}
};

// MxCollection<LegoCacheSound *>::Compare

// MxCollection<LegoCacheSound *>::~MxCollection<LegoCacheSound *>

// MxCollection<LegoCacheSound *>::Destroy

// MxList<LegoCacheSound *>::~MxList<LegoCacheSound *>

// MxPtrList<LegoCacheSound>::Destroy

// LegoCacheSoundList::`scalar deleting destructor'

// MxPtrList<LegoCacheSound>::~MxPtrList<LegoCacheSound>

// MxCollection<LegoCacheSound *>::`scalar deleting destructor'

// MxList<LegoCacheSound *>::`scalar deleting destructor'

// MxPtrList<LegoCacheSound>::`scalar deleting destructor'

// LegoCacheSoundListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoCacheSound>::~MxPtrListCursor<LegoCacheSound>

// MxListCursor<LegoCacheSound *>::`scalar deleting destructor'

// MxPtrListCursor<LegoCacheSound>::`scalar deleting destructor'

// MxListCursor<LegoCacheSound *>::~MxListCursor<LegoCacheSound *>

// LegoCacheSoundListCursor::~LegoCacheSoundListCursor

// MxListCursor<LegoCacheSound *>::MxListCursor<LegoCacheSound *>

// MxList<LegoCacheSound *>::InsertEntry

// MxListCursor<LegoCacheSound *>::Find

// MxList<LegoCacheSound *>::DeleteEntry

#endif // LEGOCACHESOUNDLIST_H
