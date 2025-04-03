#pragma once

#include "phoneme.h"
#include "mx_list.h"

// class MxCollection<LegoPhoneme *>

// class MxList<LegoPhoneme *>

class LegoPhonemeList : public MxList<LegoPhoneme*> {
public:
	LegoPhonemeList() { SetDestroy(Destroy); }

	MxS8 Compare(LegoPhoneme* p_a, LegoPhoneme* p_b) override {
		MxString a(p_a->GetName());
		MxString b(p_b->GetName());
		return a.Equal(b) ? 0 : p_a < p_b ? -1 : 1;
	}

	static void Destroy(LegoPhoneme* p_element) { delete p_element; }
};

// class MxListCursor<LegoPhoneme *>

class LegoPhonemeListCursor : public MxListCursor<LegoPhoneme*> {
public:
	LegoPhonemeListCursor(LegoPhonemeList* p_list)
		: MxListCursor<LegoPhoneme*>(p_list) {}
};

// LegoPhonemeListCursor::`scalar deleting destructor'

// MxListCursor<LegoPhoneme *>::~MxListCursor<LegoPhoneme *>

// MxListCursor<LegoPhoneme *>::`scalar deleting destructor'

// LegoPhonemeListCursor::~LegoPhonemeListCursor

// MxCollection<LegoPhoneme *>::Compare

// MxCollection<LegoPhoneme *>::~MxCollection<LegoPhoneme *>

// MxCollection<LegoPhoneme *>::Destroy

// MxList<LegoPhoneme *>::~MxList<LegoPhoneme *>

// LegoPhonemeList::`scalar deleting destructor'

// MxCollection<LegoPhoneme *>::`scalar deleting destructor'

// MxList<LegoPhoneme *>::`scalar deleting destructor'

