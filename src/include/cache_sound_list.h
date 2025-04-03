#ifndef LEGOCACHESOUNDLIST_H
#define LEGOCACHESOUNDLIST_H

#include "cach_sound.h"
#include "mx_list.h"

class LegoCacheSoundList : public MxPtrList<LegoCacheSound> {
public:
	LegoCacheSoundList(MxBool p_ownership = FALSE)
		: MxPtrList<LegoCacheSound>(p_ownership) {}

	MxS8 Compare(LegoCacheSound* p_a, LegoCacheSound* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}
};

class LegoCacheSoundListCursor : public MxPtrListCursor<LegoCacheSound> {
public:
	LegoCacheSoundListCursor(LegoCacheSoundList* p_list)
		: MxPtrListCursor<LegoCacheSound>(p_list) {}
};

#endif // LEGOCACHESOUNDLIST_H
