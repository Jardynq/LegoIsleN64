#include "legohideanimpresenter.h"

#include "anim/legoanim.h"
#include "legomain.h"
#include "legoworld.h"
#include "misc.h"

LegoHideAnimPresenter::LegoHideAnimPresenter() {
	Init();
}

LegoHideAnimPresenter::~LegoHideAnimPresenter() {
	Destroy(TRUE);
}

void LegoHideAnimPresenter::Init() {
	m_boundaryMap = NULL;
}

void LegoHideAnimPresenter::Destroy(MxBool p_fromDestructor) {
	m_criticalSection.Enter();

	if (m_boundaryMap) {
		delete[] m_boundaryMap;
	}
	Init();

	m_criticalSection.Leave();

	// This appears to be a bug, since it results in an endless loop
	if (!p_fromDestructor) {
		LegoHideAnimPresenter::Destroy();
	}
}

MxResult LegoHideAnimPresenter::AddToManager() {
	return LegoAnimPresenter::AddToManager();
}

void LegoHideAnimPresenter::Destroy() {
	Destroy(FALSE);
}

void LegoHideAnimPresenter::PutFrame() {
}

void LegoHideAnimPresenter::ReadyTickle() {
	LegoLoopingAnimPresenter::ReadyTickle();

	if (m_currentWorld) {
		if (m_currentTickleState == e_starting &&
			m_compositePresenter != NULL) {
			SendToCompositePresenter(Lego());
		}

		m_currentWorld->Add(this);
	}
}

void LegoHideAnimPresenter::StartingTickle() {
	LegoLoopingAnimPresenter::StartingTickle();

	if (m_currentTickleState == e_streaming) {
		FUN_1006dc10();
		FUN_1006db40(0);
	}
}

void LegoHideAnimPresenter::FUN_1006db40(LegoTime p_time) {
	FUN_1006db60(m_anim->GetRoot(), p_time);
}

void LegoHideAnimPresenter::FUN_1006db60(
	LegoTreeNode* p_node,
	LegoTime p_time
) {
	LegoAnimNodeData* data = (LegoAnimNodeData*) p_node->GetData();
	MxBool newB = FALSE;
	MxBool previousB = FALSE;

	if (m_roiMap != NULL) {
		LegoROI* roi = m_roiMap[data->GetUnknown0x20()];

		if (roi != NULL) {
			newB = data->FUN_100a0990(p_time);
			previousB = roi->GetVisibility();
			roi->SetVisibility(newB);
		}
	}

	if (m_boundaryMap != NULL) {
		LegoPathBoundary* boundary = m_boundaryMap[data->GetUnknown0x22()];

		if (boundary != NULL) {
			newB = data->FUN_100a0990(p_time);
			boundary->GetFlag0x10();
			// TODO: Match
			boundary->SetFlag0x10(newB);
		}
	}

	for (MxS32 i = 0; i < p_node->GetNumChildren(); i++) {
		FUN_1006db60(p_node->GetChild(i), p_time);
	}
}

void LegoHideAnimPresenter::FUN_1006dc10() {
	LegoHideAnimStructMap anims;

	FUN_1006e3f0(anims, m_anim->GetRoot());

	if (m_boundaryMap != NULL) {
		delete[] m_boundaryMap;
	}

	m_boundaryMap = new LegoPathBoundary*[anims.size() + 1];
	m_boundaryMap[0] = NULL;

	for (LegoHideAnimStructMap::iterator it = anims.begin();
		 !(it == anims.end());
		 it++) {
		m_boundaryMap[(*it).second.m_index] = (*it).second.m_boundary;
		delete[] const_cast<char*>((*it).first);
	}
}

void LegoHideAnimPresenter::FUN_1006e3f0(
	LegoHideAnimStructMap& p_map,
	LegoTreeNode* p_node
) {
	LegoAnimNodeData* data = (LegoAnimNodeData*) p_node->GetData();
	const char* name = data->GetName();

	if (name != NULL) {
		LegoPathBoundary* boundary = m_currentWorld->FindPathBoundary(name);

		if (boundary != NULL) {
			FUN_1006e470(p_map, data, name, boundary);
		} else {
			data->SetUnknown0x22(0);
		}
	}

	MxS32 count = p_node->GetNumChildren();
	for (MxS32 i = 0; i < count; i++) {
		FUN_1006e3f0(p_map, p_node->GetChild(i));
	}
}

void LegoHideAnimPresenter::FUN_1006e470(
	LegoHideAnimStructMap& p_map,
	LegoAnimNodeData* p_data,
	const char* p_name,
	LegoPathBoundary* p_boundary
) {
	LegoHideAnimStructMap::iterator it;

	it = p_map.find(p_name);
	if (it == p_map.end()) {
		LegoHideAnimStruct animStruct;
		animStruct.m_index = p_map.size() + 1;
		animStruct.m_boundary = p_boundary;

		p_data->SetUnknown0x22(animStruct.m_index);

		char* name = new char[strlen(p_name) + 1];
		strcpy(name, p_name);

		p_map[name] = animStruct;
	} else {
		p_data->SetUnknown0x22((*it).second.m_index);
	}
}

void LegoHideAnimPresenter::EndAction() {
	if (m_action) {
		MxVideoPresenter::EndAction();

		if (m_currentWorld) {
			m_currentWorld->Remove(this);
		}
	}
}
