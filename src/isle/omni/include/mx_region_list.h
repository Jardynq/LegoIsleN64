#ifndef MXREGIONLIST_H
#define MXREGIONLIST_H

#include "mx_list.h"

struct MxRegionLeftRight {
	MxRegionLeftRight(MxS32 p_left, MxS32 p_right) {
		m_left = p_left;
		m_right = p_right;
	}

	MxRegionLeftRight* Clone() {
		return new MxRegionLeftRight(m_left, m_right);
	}

	MxS32 GetLeft() { return m_left; }
	MxS32 GetRight() { return m_right; }

	void SetLeft(MxS32 p_left) { m_left = p_left; }
	void SetRight(MxS32 p_right) { m_right = p_right; }

	MxBool IntersectsWith(MxRect32& p_rect) {
		return m_left < p_rect.GetRight() && p_rect.GetTop() < m_right;
	}

private:
	MxS32 m_left;
	MxS32 m_right;
};

// class MxCollection<MxRegionLeftRight *>

// class MxList<MxRegionLeftRight *>

// class MxPtrList<MxRegionLeftRight>

class MxRegionLeftRightList : public MxPtrList<MxRegionLeftRight> {
public:
	MxRegionLeftRightList() : MxPtrList<MxRegionLeftRight>(TRUE) {}

	// MxRegionLeftRightList::`scalar deleting destructor'
};

// class MxPtrListCursor<MxRegionLeftRight>

// class MxListCursor<MxRegionLeftRight *>

class MxRegionLeftRightListCursor : public MxPtrListCursor<MxRegionLeftRight> {
public:
	MxRegionLeftRightListCursor(MxRegionLeftRightList* p_list)
		: MxPtrListCursor<MxRegionLeftRight>(p_list) {}
};

struct MxRegionTopBottom {
	MxRegionTopBottom(MxRect32& p_rect);
	MxRegionTopBottom(MxS32 p_top, MxS32 p_bottom);
	~MxRegionTopBottom() { delete m_leftRightList; }

	MxRegionTopBottom* Clone();
	void MergeOrExpandRegions(MxS32 p_left, MxS32 p_right);
	MxBool CheckHorizontalOverlap(MxRect32& p_rect);

	MxS32 GetTop() { return m_top; }
	MxS32 GetBottom() { return m_bottom; }

	void SetTop(MxS32 p_top) { m_top = p_top; }
	void SetBottom(MxS32 p_bottom) { m_bottom = p_bottom; }

	MxBool IntersectsWith(MxRect32& p_rect) {
		return m_top < p_rect.GetBottom() && p_rect.GetTop() < m_bottom;
	}

	friend class MxRegionTopBottomList;
	friend class MxRegionCursor;

private:
	MxS32 m_top;
	MxS32 m_bottom;
	MxRegionLeftRightList* m_leftRightList;
};

// class MxCollection<MxRegionTopBottom *>

// class MxList<MxRegionTopBottom *>

// class MxPtrList<MxRegionTopBottom>

class MxRegionTopBottomList : public MxPtrList<MxRegionTopBottom> {
public:
	MxRegionTopBottomList() : MxPtrList<MxRegionTopBottom>(TRUE) {}

	// MxRegionTopBottomList::`scalar deleting destructor'
};

// class MxPtrListCursor<MxRegionTopBottom>

// class MxListCursor<MxRegionTopBottom *>

// TODO: The initialize list param type should be MxRegionTopBottomList, but
// doing that drastically reduced the match percentage for MxRegion::VTable0x18.
// It also works with MxPtrList, so we'll do that until we figure this out.

class MxRegionTopBottomListCursor : public MxPtrListCursor<MxRegionTopBottom> {
public:
	MxRegionTopBottomListCursor(MxPtrList<MxRegionTopBottom>* p_list)
		: MxPtrListCursor<MxRegionTopBottom>(p_list) {}
};

// MxCollection<MxRegionTopBottom *>::Compare

// MxCollection<MxRegionTopBottom *>::~MxCollection<MxRegionTopBottom *>

// MxCollection<MxRegionTopBottom *>::Destroy

// MxList<MxRegionTopBottom *>::~MxList<MxRegionTopBottom *>

// MxPtrList<MxRegionTopBottom>::Destroy

// MxPtrList<MxRegionTopBottom>::~MxPtrList<MxRegionTopBottom>

// MxCollection<MxRegionTopBottom *>::`scalar deleting destructor'

// MxList<MxRegionTopBottom *>::`scalar deleting destructor'

// MxPtrList<MxRegionTopBottom>::`scalar deleting destructor'

// MxRegionTopBottomListCursor::`scalar deleting destructor'

// MxPtrListCursor<MxRegionTopBottom>::~MxPtrListCursor<MxRegionTopBottom>

// MxListCursor<MxRegionTopBottom *>::`scalar deleting destructor'

// MxPtrListCursor<MxRegionTopBottom>::`scalar deleting destructor'

// MxListCursor<MxRegionTopBottom *>::~MxListCursor<MxRegionTopBottom *>

// MxRegionTopBottomListCursor::~MxRegionTopBottomListCursor

// MxRegionLeftRightListCursor::`scalar deleting destructor'

// MxPtrListCursor<MxRegionLeftRight>::~MxPtrListCursor<MxRegionLeftRight>

// MxListCursor<MxRegionLeftRight *>::`scalar deleting destructor'

// MxPtrListCursor<MxRegionLeftRight>::`scalar deleting destructor'

// MxListCursor<MxRegionLeftRight *>::~MxListCursor<MxRegionLeftRight *>

// MxCollection<MxRegionLeftRight *>::Compare

// MxCollection<MxRegionLeftRight *>::~MxCollection<MxRegionLeftRight *>

// MxCollection<MxRegionLeftRight *>::Destroy

// MxList<MxRegionLeftRight *>::~MxList<MxRegionLeftRight *>

// MxPtrList<MxRegionLeftRight>::~MxPtrList<MxRegionLeftRight>

// MxCollection<MxRegionLeftRight *>::`scalar deleting destructor'

// MxPtrList<MxRegionLeftRight>::Destroy

// MxList<MxRegionLeftRight *>::`scalar deleting destructor'

// MxPtrList<MxRegionLeftRight>::`scalar deleting destructor'

// MxListCursor<MxRegionLeftRight *>::MxListCursor<MxRegionLeftRight *>

// MxRegionLeftRightListCursor::~MxRegionLeftRightListCursor

// MxListCursor<MxRegionLeftRight *>::operator=

// MxList<MxRegionLeftRight *>::InsertEntry

// MxList<MxRegionTopBottom *>::InsertEntry

// MxListEntry<MxRegionTopBottom *>::MxListEntry<MxRegionTopBottom *>

// MxList<MxRegionLeftRight *>::DeleteEntry

// MxPtrList<MxRegionTopBottom>::MxPtrList<MxRegionTopBottom>

// MxList<MxRegionTopBottom *>::MxList<MxRegionTopBottom *>

// MxCollection<MxRegionTopBottom *>::MxCollection<MxRegionTopBottom *>

// MxCollection<MxRegionTopBottom *>::SetDestroy

// MxPtrList<MxRegionTopBottom>::SetOwnership

// MxRegionTopBottomList::~MxRegionTopBottomList

// MxList<MxRegionTopBottom *>::Append

// MxPtrListCursor<MxRegionTopBottom>::MxPtrListCursor<MxRegionTopBottom>

// MxListCursor<MxRegionTopBottom *>::MxListCursor<MxRegionTopBottom *>

// MxPtrListCursor<MxRegionLeftRight>::MxPtrListCursor<MxRegionLeftRight>

// MxListCursor<MxRegionLeftRight *>::MxListCursor<MxRegionLeftRight *>

// MxRegionLeftRightListCursor::~MxRegionLeftRightListCursor

// MxPtrList<MxRegionLeftRight>::MxPtrList<MxRegionLeftRight>

// MxList<MxRegionLeftRight *>::MxList<MxRegionLeftRight *>

// MxCollection<MxRegionLeftRight *>::MxCollection<MxRegionLeftRight *>

// MxCollection<MxRegionLeftRight *>::SetDestroy

// MxPtrList<MxRegionLeftRight>::SetOwnership

// MxRegionLeftRightList::~MxRegionLeftRightList

// MxList<MxRegionLeftRight *>::Append

// MxRegionLeftRightListCursor::operator=

// MxPtrListCursor<MxRegionLeftRight>::operator=

// MxListCursor<MxRegionLeftRight *>::operator=

// MxList<MxRegionLeftRight *>::DeleteAll

// MxListCursor<MxRegionLeftRight *>::First

// MxListCursor<MxRegionLeftRight *>::Last

// MxListCursor<MxRegionLeftRight *>::Next

// MxListCursor<MxRegionLeftRight *>::Prev

// MxListCursor<MxRegionLeftRight *>::Current

// MxListCursor<MxRegionLeftRight *>::Prepend

// MxListCursor<MxRegionLeftRight *>::Destroy

// MxListCursor<MxRegionLeftRight *>::HasMatch

// MxList<MxRegionTopBottom *>::DeleteAll

// MxListCursor<MxRegionTopBottom *>::Next

// MxListCursor<MxRegionTopBottom *>::Prev

// MxListCursor<MxRegionTopBottom *>::Prepend

// MxListCursor<MxRegionTopBottom *>::Destroy

// MxListEntry<MxRegionLeftRight *>::MxListEntry<MxRegionLeftRight *>

// MxListEntry<MxRegionLeftRight *>::GetPrev

// MxListEntry<MxRegionLeftRight *>::SetPrev

// MxListEntry<MxRegionLeftRight *>::GetNext

// MxListEntry<MxRegionLeftRight *>::SetNext

// MxListEntry<MxRegionLeftRight *>::GetValue

// MxListEntry<MxRegionTopBottom *>::GetPrev

// MxListEntry<MxRegionTopBottom *>::SetPrev

// MxListEntry<MxRegionTopBottom *>::GetNext

// MxListEntry<MxRegionTopBottom *>::SetNext

// MxListEntry<MxRegionTopBottom *>::GetValue

// MxList<MxRegionTopBottom *>::DeleteEntry

#endif // MXREGIONLIST_H
