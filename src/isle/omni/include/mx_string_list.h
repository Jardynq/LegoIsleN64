#pragma once

#include "mx_list.h"
#include "mx_string.h"

class MxStringList : public MxList<MxString> {};

// MxStringList::MxStringList

// MxStringList::`scalar deleting destructor'

// MxStringList::~MxStringList

class MxStringListCursor : public MxListCursor<MxString> {
public:
	MxStringListCursor(MxStringList* p_list) : MxListCursor<MxString>(p_list) {}
};

// class MxCollection<MxString>

// class MxList<MxString>

// class MxListCursor<MxString>

// MxCollection<MxString>::Compare

// MxCollection<MxString>::~MxCollection<MxString>

// MxCollection<MxString>::Destroy

// MxList<MxString>::~MxList<MxString>

// MxCollection<MxString>::`scalar deleting destructor'

// MxList<MxString>::`scalar deleting destructor'

// MxList<MxString>::Append

// MxList<MxString>::InsertEntry

// MxListEntry<MxString>::MxListEntry<MxString>

// MxListEntry<MxString>::GetValue

// MxList<MxString>::MxList<MxString>

// MxCollection<MxString>::MxCollection<MxString>

// MxCollection<MxString>::SetDestroy

// MxListCursor<MxString>::MxListCursor<MxString>

// MxList<MxString>::DeleteAll

// MxListCursor<MxString>::Next

// MxListEntry<MxString>::SetPrev

// MxListEntry<MxString>::GetNext

// MxListEntry<MxString>::SetNext

// MxListEntry<MxString>::`scalar deleting destructor'

// MxListEntry<MxString>::~MxListEntry<MxString>

