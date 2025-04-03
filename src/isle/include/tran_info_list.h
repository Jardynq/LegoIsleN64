#pragma once

#include "tran_info.h"
#include "mx_list.h"

// class MxCollection<LegoTranInfo *>

// class MxList<LegoTranInfo *>

// class MxPtrList<LegoTranInfo>

class LegoTranInfoList : public MxPtrList<LegoTranInfo> {
public:
	LegoTranInfoList() : MxPtrList<LegoTranInfo>(FALSE) {}
};

// class MxListCursor<LegoTranInfo *>

// class MxPtrListCursor<LegoTranInfo>

class LegoTranInfoListCursor : public MxPtrListCursor<LegoTranInfo> {
public:
	LegoTranInfoListCursor(LegoTranInfoList* p_list)
		: MxPtrListCursor<LegoTranInfo>(p_list) {}
};

// MxCollection<LegoTranInfo *>::Compare

// MxCollection<LegoTranInfo *>::~MxCollection<LegoTranInfo *>

// MxCollection<LegoTranInfo *>::Destroy

// MxList<LegoTranInfo *>::~MxList<LegoTranInfo *>

// LegoTranInfoList::`scalar deleting destructor'

// MxPtrList<LegoTranInfo>::~MxPtrList<LegoTranInfo>

// MxCollection<LegoTranInfo *>::`scalar deleting destructor'

// MxList<LegoTranInfo *>::`scalar deleting destructor'

// MxPtrList<LegoTranInfo>::`scalar deleting destructor'

// LegoTranInfoListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoTranInfo>::~MxPtrListCursor<LegoTranInfo>

// MxListCursor<LegoTranInfo *>::`scalar deleting destructor'

// MxPtrListCursor<LegoTranInfo>::`scalar deleting destructor'

// MxListCursor<LegoTranInfo *>::~MxListCursor<LegoTranInfo *>

// LegoTranInfoListCursor::~LegoTranInfoListCursor

