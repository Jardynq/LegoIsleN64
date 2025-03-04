#ifndef MXRECTLIST_H
#define MXRECTLIST_H

#include "mxlist.h"
#include "mxrect32.h"

class MxRectList : public MxPtrList<MxRect32> {
public:
	MxRectList(MxBool p_ownership = FALSE) : MxPtrList<MxRect32>(p_ownership) {}
};

// class MxListCursor<MxRect32 *>

// class MxPtrListCursor<MxRect32>

class MxRectListCursor : public MxPtrListCursor<MxRect32> {
public:
	MxRectListCursor(MxRectList* p_list) : MxPtrListCursor<MxRect32>(p_list) {}
};

// class MxPtrList<MxRect32>

// class MxList<MxRect32 *>

// class MxCollection<MxRect32 *>

// MxCollection<MxRect32 *>::Compare

// MxCollection<MxRect32 *>::MxCollection<MxRect32 *>

// MxCollection<MxRect32 *>::~MxCollection<MxRect32 *>

// MxCollection<MxRect32 *>::Destroy

// MxList<MxRect32 *>::~MxList<MxRect32 *>

// MxPtrList<MxRect32>::Destroy

// MxRectList::`scalar deleting destructor'

// MxPtrList<MxRect32>::~MxPtrList<MxRect32>

// MxCollection<MxRect32 *>::`scalar deleting destructor'

// MxList<MxRect32 *>::`scalar deleting destructor'

// MxPtrList<MxRect32>::`scalar deleting destructor'

// MxRectList::~MxRectList

// MxRectListCursor::`scalar deleting destructor'

// MxPtrListCursor<MxRect32>::~MxPtrListCursor<MxRect32>

// MxListCursor<MxRect32 *>::`scalar deleting destructor'

// MxPtrListCursor<MxRect32>::`scalar deleting destructor'

// MxListCursor<MxRect32 *>::~MxListCursor<MxRect32 *>

// MxRectListCursor::~MxRectListCursor

// MxPtrList<MxRect32>::MxPtrList<MxRect32>

// MxList<MxRect32 *>::MxList<MxRect32 *>

// MxCollection<MxRect32 *>::SetDestroy

// MxPtrList<MxRect32>::SetOwnership

// MxPtrListCursor<MxRect32>::MxPtrListCursor<MxRect32>

// MxListCursor<MxRect32 *>::MxListCursor<MxRect32 *>

// MxList<MxRect32 *>::DeleteAll

// MxListCursor<MxRect32 *>::Next

// MxListEntry<MxRect32 *>::GetNext

// MxListEntry<MxRect32 *>::GetValue

// MxList<MxRect32 *>::Append

// MxList<MxRect32 *>::InsertEntry

// MxListEntry<MxRect32 *>::MxListEntry<MxRect32 *>

// MxListEntry<MxRect32 *>::SetPrev

// MxListEntry<MxRect32 *>::SetNext

#endif // MXRECTLIST_H
