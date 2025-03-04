#ifndef MXDSACTIONLIST_H
#define MXDSACTIONLIST_H

#include "mxdsaction.h"
#include "mxlist.h"

// class MxCollection<MxDSAction *>

// class MxList<MxDSAction *>

class MxDSActionList : public MxList<MxDSAction*> {
public:
	MxDSActionList() { this->m_unk0x18 = 0; }

	MxS8 Compare(MxDSAction* p_a, MxDSAction* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}

	static void Destroy(MxDSAction* p_action) { delete p_action; }

	// MxDSActionList::`scalar deleting destructor'

private:
	undefined m_unk0x18;
};

// class MxListCursor<MxDSAction *>

class MxDSActionListCursor : public MxListCursor<MxDSAction*> {
public:
	MxDSActionListCursor(MxDSActionList* p_list)
		: MxListCursor<MxDSAction*>(p_list) {}
};

// MxCollection<MxDSAction *>::Compare

// MxCollection<MxDSAction *>::~MxCollection<MxDSAction *>

// MxCollection<MxDSAction *>::Destroy

// MxList<MxDSAction *>::~MxList<MxDSAction *>

// MxCollection<MxDSAction *>::`scalar deleting destructor'

// MxList<MxDSAction *>::`scalar deleting destructor'

// MxListCursor<MxDSAction *>::MxListCursor<MxDSAction *>

// MxListCursor<MxDSAction *>::Head

// ?Next@?$MxListCursor@PAVMxDSAction@@@@QAEEXZ

// MxListCursor<MxDSAction *>::Current

// MxListEntry<MxDSAction *>::GetNext

// MxListEntry<MxDSAction *>::GetValue

// ?Next@?$MxListCursor@PAVMxDSAction@@@@QAEEAAPAVMxDSAction@@@Z

// MxListCursor<MxDSAction *>::Find

// MxListCursor<MxDSAction *>::Detach

// MxList<MxDSAction *>::DeleteEntry

// MxListEntry<MxDSAction *>::GetPrev

// MxListEntry<MxDSAction *>::SetPrev

// MxListEntry<MxDSAction *>::SetNext

// MxCollection<MxDSAction *>::SetDestroy

// MxList<MxDSAction *>::MxList<MxDSAction *>

// MxCollection<MxDSAction *>::MxCollection<MxDSAction *>

// MxDSActionList::~MxDSActionList

// MxList<MxDSAction *>::Append

// MxList<MxDSAction *>::InsertEntry

// MxListEntry<MxDSAction *>::MxListEntry<MxDSAction *>

// MxList<MxDSAction *>::DeleteAll

#endif // MXDSACTIONLIST_H
