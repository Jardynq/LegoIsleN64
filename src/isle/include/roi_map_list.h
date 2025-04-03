#ifndef LEGOROIMAPLIST_H
#define LEGOROIMAPLIST_H

#include "mx_list.h"

class LegoROI;

// class MxCollection<LegoROI **>

// class MxList<LegoROI **>

// class MxPtrList<LegoROI *>

class LegoROIMapList : public MxPtrList<LegoROI*> {
public:
	LegoROIMapList() : MxPtrList<LegoROI*>(TRUE) {}

	// LegoROIMapList::`scalar deleting destructor'
};

// MxCollection<LegoROI * *>::Compare

// MxCollection<LegoROI * *>::~MxCollection<LegoROI * *>

// MxCollection<LegoROI * *>::Destroy

// MxList<LegoROI * *>::~MxList<LegoROI * *>

// MxPtrList<LegoROI *>::~MxPtrList<LegoROI *>

// MxPtrList<LegoROI *>::Destroy

// MxCollection<LegoROI * *>::`scalar deleting destructor'

// MxList<LegoROI * *>::`scalar deleting destructor'

// MxPtrList<LegoROI *>::`scalar deleting destructor'

#endif // LEGOROIMAPLIST_H
