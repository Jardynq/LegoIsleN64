#ifndef MXPRESENTERLIST_H
#define MXPRESENTERLIST_H

#include "mxlist.h"
#include "mxpresenter.h"

// class MxPtrList<MxPresenter>

class MxPresenterList : public MxPtrList<MxPresenter> {
public:
	MxPresenterList(MxBool p_ownership = FALSE)
		: MxPtrList<MxPresenter>(p_ownership) {}

	MxS8 Compare(MxPresenter* p_a, MxPresenter* p_b) override {
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	}

	// MxPresenterList::`scalar deleting destructor'
};

// class MxListCursor<MxPresenter *>

// class MxPtrListCursor<MxPresenter>

class MxPresenterListCursor : public MxPtrListCursor<MxPresenter> {
public:
	MxPresenterListCursor(MxPresenterList* p_list)
		: MxPtrListCursor<MxPresenter>(p_list) {}
};

// class MxCollection<MxPresenter *>

// class MxList<MxPresenter *>

// MxCollection<MxPresenter *>::Compare

// MxCollection<MxPresenter *>::Destroy

// MxList<MxPresenter *>::MxList<MxPresenter *>

// MxCollection<MxPresenter *>::~MxCollection<MxPresenter *>

// MxList<MxPresenter *>::~MxList<MxPresenter *>

// MxPtrList<MxPresenter>::~MxPtrList<MxPresenter>

// MxCollection<MxPresenter *>::`scalar deleting destructor'

// MxList<MxPresenter *>::`scalar deleting destructor'

// MxPtrList<MxPresenter>::`scalar deleting destructor'

// MxPresenterList::~MxPresenterList

// MxPresenterListCursor::`scalar deleting destructor'

// MxPtrListCursor<MxPresenter>::~MxPtrListCursor<MxPresenter>

// MxListCursor<MxPresenter *>::`scalar deleting destructor'

// MxPtrListCursor<MxPresenter>::`scalar deleting destructor'

// MxListCursor<MxPresenter *>::~MxListCursor<MxPresenter *>

// MxPresenterListCursor::~MxPresenterListCursor

// MxListCursor<MxPresenter *>::MxListCursor<MxPresenter *>

// MxList<MxPresenter *>::InsertEntry

// MxList<MxPresenter *>::DeleteEntry

// MxPtrListCursor<MxPresenter>::MxPtrListCursor<MxPresenter>

// MxListCursor<MxPresenter *>::MxListCursor<MxPresenter *>

// MxListCursor<MxPresenter *>::Prev

#endif // MXPRESENTERLIST_H
