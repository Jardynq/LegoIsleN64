#ifndef LEGOENTITYLIST_H
#define LEGOENTITYLIST_H

#include "entity.h"
#include "mx_list.h"

// class MxCollection<LegoEntity *>

// class MxList<LegoEntity *>

// class MxPtrList<LegoEntity>

class LegoEntityList : public MxPtrList<LegoEntity> {
public:
	LegoEntityList(MxBool p_ownership = FALSE)
		: MxPtrList<LegoEntity>(p_ownership) {}

	MxS8 Compare(LegoEntity* p_a, LegoEntity* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}
};

// class MxListCursor<LegoEntity *>

// class MxPtrListCursor<LegoEntity>

class LegoEntityListCursor : public MxPtrListCursor<LegoEntity> {
public:
	LegoEntityListCursor(LegoEntityList* p_list)
		: MxPtrListCursor<LegoEntity>(p_list) {}
};

// MxCollection<LegoEntity *>::Compare

// MxCollection<LegoEntity *>::~MxCollection<LegoEntity *>

// MxCollection<LegoEntity *>::Destroy

// MxList<LegoEntity *>::~MxList<LegoEntity *>

// MxPtrList<LegoEntity>::Destroy

// LegoEntityList::`scalar deleting destructor'

// MxPtrList<LegoEntity>::~MxPtrList<LegoEntity>

// MxCollection<LegoEntity *>::`scalar deleting destructor'

// MxList<LegoEntity *>::`scalar deleting destructor'

// MxPtrList<LegoEntity>::`scalar deleting destructor'

// LegoEntityListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoEntity>::~MxPtrListCursor<LegoEntity>

// MxListCursor<LegoEntity *>::`scalar deleting destructor'

// MxPtrListCursor<LegoEntity>::`scalar deleting destructor'

// MxListCursor<LegoEntity *>::~MxListCursor<LegoEntity *>

// LegoEntityListCursor::~LegoEntityListCursor

// MxListCursor<LegoEntity *>::MxListCursor<LegoEntity *>

// MxList<LegoEntity *>::InsertEntry

// MxList<LegoEntity *>::DeleteEntry

#endif // LEGOENTITYLIST_H
