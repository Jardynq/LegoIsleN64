#pragma once

#include "mx_list.h"
#include "lod.h"

#pragma warning(disable : 4786)

// class MxCollection<LegoLOD *>

// class MxList<LegoLOD *>

// class MxPtrList<LegoLOD>

class LegoLODList : public MxPtrList<LegoLOD> {
public:
	LegoLODList() : MxPtrList<LegoLOD>(FALSE) {}

	// LegoLODList::`scalar deleting destructor'
};

// class MxListCursor<LegoLOD *>

// class MxPtrListCursor<LegoLOD>

class LegoLODListCursor : public MxPtrListCursor<LegoLOD> {
public:
	LegoLODListCursor(LegoLODList* p_list) : MxPtrListCursor<LegoLOD>(p_list) {}
};

// LegoLODListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoLOD>::~MxPtrListCursor<LegoLOD>

// MxListCursor<LegoLOD *>::`scalar deleting destructor'

// MxPtrListCursor<LegoLOD>::`scalar deleting destructor'

// MxListCursor<LegoLOD *>::~MxListCursor<LegoLOD *>

// LegoLODListCursor::~LegoLODListCursor

// MxCollection<LegoLOD *>::Compare

// MxCollection<LegoLOD *>::~MxCollection<LegoLOD *>

// MxCollection<LegoLOD *>::Destroy

// MxList<LegoLOD *>::~MxList<LegoLOD *>

// MxCollection<LegoLOD *>::`scalar deleting destructor'

// MxList<LegoLOD *>::`scalar deleting destructor'

// MxPtrList<LegoLOD>::`scalar deleting destructor'

// MxPtrList<LegoLOD>::~MxPtrList<LegoLOD>

