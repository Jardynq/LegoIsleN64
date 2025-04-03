#ifndef LEGOWORLDLIST_H
#define LEGOWORLDLIST_H

#include "mx_list.h"

class LegoWorld;

// class MxCollection<LegoWorld *>

// class MxList<LegoWorld *>

// class MxPtrList<LegoWorld>

class LegoWorldList : public MxPtrList<LegoWorld> {
public:
	LegoWorldList(MxBool p_ownership = FALSE)
		: MxPtrList<LegoWorld>(p_ownership) {}

	MxS8 Compare(LegoWorld* p_a, LegoWorld* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}

	// LegoWorldList::`scalar deleting destructor'
};

// class MxListCursor<LegoWorld *>

// class MxPtrListCursor<LegoWorld>

class LegoWorldListCursor : public MxPtrListCursor<LegoWorld> {
public:
	LegoWorldListCursor(LegoWorldList* p_list)
		: MxPtrListCursor<LegoWorld>(p_list) {}
};

// LegoWorldListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoWorld>::~MxPtrListCursor<LegoWorld>

// MxListCursor<LegoWorld *>::`scalar deleting destructor'

// MxPtrListCursor<LegoWorld>::`scalar deleting destructor'

// MxListCursor<LegoWorld *>::~MxListCursor<LegoWorld *>

// LegoWorldListCursor::~LegoWorldListCursor

// MxCollection<LegoWorld *>::Compare

// MxCollection<LegoWorld *>::~MxCollection<LegoWorld *>

// MxCollection<LegoWorld *>::Destroy

// MxList<LegoWorld *>::~MxList<LegoWorld *>

// MxPtrList<LegoWorld>::Destroy

// MxPtrList<LegoWorld>::~MxPtrList<LegoWorld>

// MxCollection<LegoWorld *>::`scalar deleting destructor'

// MxList<LegoWorld *>::`scalar deleting destructor'

// MxPtrList<LegoWorld>::`scalar deleting destructor'

// MxList<LegoWorld *>::DeleteEntry

#endif // LEGOWORLDLIST_H
