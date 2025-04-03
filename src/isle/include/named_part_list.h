#ifndef LEGONAMEDPARTLIST_H
#define LEGONAMEDPARTLIST_H

#include "named_part.h"
#include "mx_list.h"

// class MxCollection<LegoNamedPart *>

// class MxList<LegoNamedPart *>

// class MxPtrList<LegoNamedPart>

class LegoNamedPartList : public MxPtrList<LegoNamedPart> {
public:
	LegoNamedPartList() : MxPtrList<LegoNamedPart>(TRUE) {}

	// LegoNamedPartList::`scalar deleting destructor'
};

// class MxListCursor<LegoNamedPart *>

// class MxPtrListCursor<LegoNamedPart>

class LegoNamedPartListCursor : public MxPtrListCursor<LegoNamedPart> {
public:
	LegoNamedPartListCursor(LegoNamedPartList* p_list)
		: MxPtrListCursor<LegoNamedPart>(p_list) {}
};

// LegoNamedPartListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoNamedPart>::~MxPtrListCursor<LegoNamedPart>

// MxListCursor<LegoNamedPart *>::`scalar deleting destructor'

// MxPtrListCursor<LegoNamedPart>::`scalar deleting destructor'

// MxListCursor<LegoNamedPart *>::~MxListCursor<LegoNamedPart *>

// LegoNamedPartListCursor::~LegoNamedPartListCursor

// MxCollection<LegoNamedPart *>::Compare

// MxCollection<LegoNamedPart *>::~MxCollection<LegoNamedPart *>

// MxCollection<LegoNamedPart *>::Destroy

// MxList<LegoNamedPart *>::~MxList<LegoNamedPart *>

// MxPtrList<LegoNamedPart>::Destroy

// MxPtrList<LegoNamedPart>::~MxPtrList<LegoNamedPart>

// MxCollection<LegoNamedPart *>::`scalar deleting destructor'

// MxList<LegoNamedPart *>::`scalar deleting destructor'

// MxPtrList<LegoNamedPart>::`scalar deleting destructor'

#endif // LEGONAMEDPARTLIST_H
