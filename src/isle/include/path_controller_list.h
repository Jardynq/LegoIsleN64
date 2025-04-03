#ifndef LEGOPATHCONTROLLERLIST_H
#define LEGOPATHCONTROLLERLIST_H

#include "path_controller.h"
#include "mx_list.h"

// class MxCollection<LegoPathController *>

// class MxList<LegoPathController *>

// class MxPtrList<LegoPathController>

class LegoPathControllerList : public MxPtrList<LegoPathController> {
public:
	LegoPathControllerList(MxBool p_ownership = FALSE)
		: MxPtrList<LegoPathController>(p_ownership) {}

	MxS8 Compare(LegoPathController* p_a, LegoPathController* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}
};

// class MxListCursor<LegoPathController *>

// class MxPtrListCursor<LegoPathController>

class LegoPathControllerListCursor
	: public MxPtrListCursor<LegoPathController> {
public:
	LegoPathControllerListCursor(LegoPathControllerList* p_list)
		: MxPtrListCursor<LegoPathController>(p_list) {}
};

// MxCollection<LegoPathController *>::Compare

// MxList<LegoPathController *>::MxList<LegoPathController *>

// MxCollection<LegoPathController *>::~MxCollection<LegoPathController *>

// MxCollection<LegoPathController *>::Destroy

// MxList<LegoPathController *>::~MxList<LegoPathController *>

// MxPtrList<LegoPathController>::Destroy

// LegoPathControllerList::`scalar deleting destructor'

// MxPtrList<LegoPathController>::~MxPtrList<LegoPathController>

// MxCollection<LegoPathController *>::`scalar deleting destructor'

// MxList<LegoPathController *>::`scalar deleting destructor'

// MxPtrList<LegoPathController>::`scalar deleting destructor'

// LegoPathControllerList::~LegoPathControllerList

// LegoPathControllerListCursor::`scalar deleting destructor'

// MxPtrListCursor<LegoPathController>::~MxPtrListCursor<LegoPathController>

// MxListCursor<LegoPathController *>::`scalar deleting destructor'

// MxPtrListCursor<LegoPathController>::`scalar deleting destructor'

// MxListCursor<LegoPathController *>::~MxListCursor<LegoPathController *>

// LegoPathControllerListCursor::~LegoPathControllerListCursor

// MxPtrList<LegoPathController>::MxPtrList<LegoPathController>

// MxCollection<LegoPathController *>::MxCollection<LegoPathController *>

// MxCollection<LegoPathController *>::SetDestroy

// MxPtrList<LegoPathController>::SetOwnership

// MxPtrListCursor<LegoPathController>::MxPtrListCursor<LegoPathController>

// MxListCursor<LegoPathController *>::MxListCursor<LegoPathController *>

// MxList<LegoPathController *>::DeleteAll

// MxListCursor<LegoPathController *>::Next

// MxListEntry<LegoPathController *>::GetNext

// MxListEntry<LegoPathController *>::GetValue

#endif // LEGOPATHCONTROLLERLIST_H
