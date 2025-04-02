#include "viewlodlist.h"

#include "viewlod.h"

#include <stdio.h>

int ViewLODListManager::g_ROINameUID = 0;

ViewLODListManager::ViewLODListManager() {
}

ViewLODListManager::~ViewLODListManager() {
	ViewLODListMap::iterator iterator;

	// delete all ViewLODLists
	for (iterator = m_map.begin(); !(iterator == m_map.end()); ++iterator) {
		const ROIName& rROIName = (*iterator).first;
		ViewLODList* pLODList = (*iterator).second;

		// ???who pops and deletes LODObjects
		while (pLODList->Size() > 0) {
			delete const_cast<ViewLOD*>(pLODList->PopBack());
		}

		delete pLODList;
		// ??? for now
		delete[] const_cast<char*>(rROIName);
	}

	// ??? correct way of "emptying" map
	m_map.erase(m_map.begin(), m_map.end());

	assert(m_map.begin() == m_map.end());
}

ViewLODList* ViewLODListManager::Create(const ROIName& rROIName, int lodCount) {
	// returned ViewLODList has a refCount of 1, i.e. caller must call Release()
	// when it no longer holds on to the list

	ViewLODList* pLODList = nullptr;
	int refCount = 0;
	char* pROIName = nullptr;

	// assert(!Lookup(rROIName)); // alpha only

	pLODList = new ViewLODList(lodCount, this);
	refCount = pLODList->AddRef();
	assert(refCount == 1);

	ViewLODList* list = Lookup(rROIName);
	if (list != NULL) {
		list->Release();

		char num[12];
		sprintf(num, "%d", g_ROINameUID);
		pROIName = new char[strlen(rROIName) + strlen(num) + 1];
		strcpy(pROIName, rROIName);
		strcat(pROIName, num);
		g_ROINameUID++;
	} else {
		pROIName = new char[strlen(rROIName) + 1];
		strcpy(pROIName, rROIName);
	}

	m_map[pROIName] = pLODList;

	// NOTE: Lookup() adds a refCount
	assert((Lookup(pROIName) == pLODList) && (pLODList->Release() == 1));

	return pLODList;
}

ViewLODList* ViewLODListManager::Lookup(const ROIName& p_roiName) const {
	// returned ViewLODList's refCount is increased, i.e. caller must call
	// Release() when it no longer holds on to the list

	ViewLODListMap::const_iterator iterator = m_map.find(p_roiName);
	ViewLODList* pLODList = 0;

	if (!(iterator == m_map.end())) {
		pLODList = (*iterator).second;

		assert(pLODList);
		pLODList->AddRef();
	}

	return pLODList;
}

unsigned char ViewLODListManager::Destroy(ViewLODList* lodList) {
	ViewLODListMap::iterator iterator;
	char deleted = FALSE;

	for (iterator = m_map.begin(); !(iterator == m_map.end()); ++iterator) {
		const ROIName& rROIName = (*iterator).first;
		ViewLODList* pLODList = (*iterator).second;

		if (lodList == pLODList) {
			while (pLODList->Size() > 0) {
				delete const_cast<ViewLOD*>(pLODList->PopBack());
			}

			delete pLODList;
			delete[] const_cast<char*>(rROIName);
			m_map.erase(iterator);

			deleted = TRUE;
			break;
		}
	}

	return deleted;
}
