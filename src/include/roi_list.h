#ifndef LEGOROILIST_H
#define LEGOROILIST_H

#include "mx_list.h"
#include "roi.h"

// class MxCollection<LegoROI *>

// class MxList<LegoROI *>

// class MxPtrList<LegoROI>

class LegoROIList : public MxPtrList<LegoROI> {
public:
	LegoROIList(MxBool p_ownership = FALSE) : MxPtrList<LegoROI>(p_ownership) {}

	MxS8 Compare(LegoROI* p_a, LegoROI* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}

	// LegoROIList::`scalar deleting destructor'
};

// class MxListCursor<LegoROI *>

// class MxPtrListCursor<LegoROI>

class LegoROIListCursor : public MxPtrListCursor<LegoROI> {
public:
	LegoROIListCursor(LegoROIList* p_list) : MxPtrListCursor<LegoROI>(p_list) {}
};

// MxCollection<LegoROI *>::Compare

// MxCollection<LegoROI *>::~MxCollection<LegoROI *>

// MxCollection<LegoROI *>::Destroy

// MxList<LegoROI *>::~MxList<LegoROI *>

// MxPtrList<LegoROI>::~MxPtrList<LegoROI>

// MxCollection<LegoROI *>::`scalar deleting destructor'

// MxList<LegoROI *>::`scalar deleting destructor'

// MxPtrList<LegoROI>::`scalar deleting destructor'

// LegoROIListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoROI>::~MxPtrListCursor<LegoROI>

// MxListCursor<LegoROI *>::`scalar deleting destructor'

// MxPtrListCursor<LegoROI>::`scalar deleting destructor'

// MxListCursor<LegoROI *>::~MxListCursor<LegoROI *>

// LegoROIListCursor::~LegoROIListCursor

// MxListEntry<LegoROI *>::MxListEntry<LegoROI *>

#endif // LEGOROILIST_H
