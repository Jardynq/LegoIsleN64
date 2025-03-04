#ifndef VIEWLODLIST_H
#define VIEWLODLIST_H

#include "assert.h"
#include "realtime/lodlist.h"

#include <string.h>

#pragma warning(disable : 4237)
#pragma warning(disable : 4786)

class ViewLOD;
class ViewLODListManager;

//////////////////////////////////////////////////////////////////////////////
// ViewLODList
//
// An ViewLODList is an LODList that is shared among instances of the "same
// ROI".
//
// ViewLODLists are managed (created and destroyed) by ViewLODListManager.
//

class ViewLODList : public LODList<ViewLOD> {
	friend ViewLODListManager;

protected:
	ViewLODList(size_t capacity, ViewLODListManager* owner);
	~ViewLODList() override;

	// ViewLODList::`scalar deleting destructor'

public:
	inline int AddRef();
	inline int Release();

private:
	int m_refCount;
	ViewLODListManager* m_owner;
};

//////////////////////////////////////////////////////////////////////////////
//

// ??? for now, until we have symbol management
typedef const char* ROIName;
struct ROINameComparator {

	unsigned char
	operator()(const ROIName& rName1, const ROIName& rName2) const {
		return strcmp((const char*) rName1, (const char*) rName2) > 0;
	}
};

//////////////////////////////////////////////////////////////////////////////
//
// ViewLODListManager
//
// ViewLODListManager manages creation and sharing of ViewLODLists.
// It stores ViewLODLists under a name, the name of the ROI where
// the ViewLODList belongs.

class ViewLODListManager {

	typedef map<ROIName, ViewLODList*, ROINameComparator> ViewLODListMap;

public:
	ViewLODListManager();
	virtual ~ViewLODListManager();

	// ??? should LODList be const

	// creates an LODList with room for lodCount LODs for a named ROI
	// returned LODList has a refCount of 1, i.e. caller must call Release()
	// when it no longer holds on to the list
	ViewLODList* Create(const ROIName& rROIName, int lodCount);

	// returns an LODList for a named ROI
	// returned LODList's refCount is increased, i.e. caller must call Release()
	// when it no longer holds on to the list
	ViewLODList* Lookup(const ROIName&) const;
	unsigned char Destroy(ViewLODList* lodList);

	// ViewLODListManager::`scalar deleting destructor'

private:
	static int g_ROINameUID;

	ViewLODListMap m_map;
};

// clang-format off


// _Lockit::~_Lockit



// Map<char const *,ViewLODList *,ROINameComparator>::~Map<char const *,ViewLODList *,ROINameComparator>


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::iterator::_Dec


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::iterator::_Inc


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::~_Tree<char const *,pair<char const * const,ViewLODList *>,map<char c



// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::erase



// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::_Erase



// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::_Insert



// map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::~map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >



// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::_Nil


// map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::operator[]


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::iterator::operator==


// map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::begin


// map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::end


// pair<char const * const,ViewLODList *>::pair<char const * const,ViewLODList *>


// map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::insert


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::insert


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::iterator::operator*


// map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::erase
// No symbol generated for this?
// Two iterators


// ?erase@?$map@PBDPAVViewLODList@@UROINameComparator@@V?$allocator@PAVViewLODList@@@@@@QAE?AViterator@?$_Tree@PBDU?$pair@QBDPAVViewLODList@@@@U_Kfn@?$map@PBDPAVViewLODList@@UROINameComparator@@V?$allocator@PAVViewLODList@@@@@@UROINameComparator@@V?$allocato
// aka map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::erase
// One iterator


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::_Lmost


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::_Rmost


// _Tree<char const *,pair<char const * const,ViewLODList *>,map<char const *,ViewLODList *,ROINameComparator,allocator<ViewLODList *> >::_Kfn,ROINameComparator,allocator<ViewLODList *> >::_Color


// ?swap@@YAXAAW4_Redbl@?$_Tree@PBDU?$pair@QBDPAVViewLODList@@@@U_Kfn@?$map@PBDPAVViewLODList@@UROINameComparator@@V?$allocator@PAVViewLODList@@@@@@UROINameComparator@@V?$allocator@PAVViewLODList@@@@@@0@Z

// clang-format on

//////////////////////////////////////////////////////////////////////////////
//
// ViewLODList implementation

inline ViewLODList::ViewLODList(size_t capacity, ViewLODListManager* owner)
	: LODList<ViewLOD>(capacity), m_refCount(0), m_owner(owner) {
}

inline ViewLODList::~ViewLODList() {
	assert(m_refCount == 0);
}

inline int ViewLODList::AddRef() {
	return ++m_refCount;
}

inline int ViewLODList::Release() {
	assert(m_refCount > 0);
	if (!--m_refCount) {
		m_owner->Destroy(this);
		return 0;
	}

	return m_refCount;
}

#endif // VIEWLODLIST_H
