#include "locomotion_anim_presenter.h"

#include "anim.h"
#include "anim_actor.h"
#include "legomain.h"
#include "world.h"
#include "misc.h"
#include "mxautolock.h"
#include "mx_ds_subscriber.h"
#include "mx_misc.h"
#include "mx_variable_table.h"

LegoLocomotionAnimPresenter::LegoLocomotionAnimPresenter() {
	Init();
}

LegoLocomotionAnimPresenter::~LegoLocomotionAnimPresenter() {
	Destroy(TRUE);
}

void LegoLocomotionAnimPresenter::Init() {
	m_unk0xc0 = 0;
	m_unk0xc4 = NULL;
	m_unk0xcc = -1;
	m_unk0xd0 = -1;
	m_roiMapList = NULL;
	m_unk0xd4 = 0;
}

void LegoLocomotionAnimPresenter::Destroy(MxBool p_fromDestructor) {
	m_criticalSection.Enter();

	if (m_unk0xc4) {
		delete[] m_unk0xc4;
	}

	if (m_roiMapList) {
		delete m_roiMapList;
	}

	m_roiMap = NULL;
	Init();

	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		LegoLoopingAnimPresenter::Destroy();
	}
}

MxResult LegoLocomotionAnimPresenter::CreateAnim(MxStreamChunk* p_chunk) {
	MxResult result = LegoAnimPresenter::CreateAnim(p_chunk);
	return result == SUCCESS ? SUCCESS : result;
}

MxResult LegoLocomotionAnimPresenter::AddToManager() {
	m_roiMapList = new LegoROIMapList();

	if (m_roiMapList == NULL) {
		return FAILURE;
	}

	return LegoAnimPresenter::AddToManager();
}

void LegoLocomotionAnimPresenter::Destroy() {
	Destroy(FALSE);
}

void LegoLocomotionAnimPresenter::PutFrame() {
	// Empty
}

void LegoLocomotionAnimPresenter::ReadyTickle() {
	LegoLoopingAnimPresenter::ReadyTickle();

	if (m_currentWorld != NULL && m_currentTickleState == e_starting) {
		m_currentWorld->Add(this);
		if (m_compositePresenter != NULL) {
			SendToCompositePresenter(Lego());
		}

		m_unk0xd4++;
	}
}

void LegoLocomotionAnimPresenter::StartingTickle() {
	if (m_subscriber->PeekData()) {
		MxStreamChunk* chunk = m_subscriber->PopData();
		m_subscriber->FreeDataChunk(chunk);
	}

	if (m_roiMapList->GetCount() != 0) {
		ProgressTickleState(e_streaming);
	}
}

void LegoLocomotionAnimPresenter::StreamingTickle() {
	if (m_unk0xd4 == 0) {
		EndAction();
	}
}

void LegoLocomotionAnimPresenter::EndAction() {
	if (m_action) {
		MxVideoPresenter::EndAction();
	}
}

void LegoLocomotionAnimPresenter::FUN_1006d680(
	LegoAnimActor* p_actor,
	MxFloat p_value
) {
	AUTOLOCK(m_criticalSection);

	MxVariableTable* variableTable = VariableTable();

	const char* key =
		((LegoAnimNodeData*) m_anim->GetRoot()->GetData())->GetName();
	variableTable->SetVariable(key, p_actor->GetROI()->GetName());

	FUN_100695c0();
	FUN_10069b10();

	if (m_roiMap != NULL) {
		m_roiMapList->Append(m_roiMap);
		p_actor->FUN_1001c450(m_anim, p_value, m_roiMap, m_roiMapSize);
		m_roiMap = NULL;
	}

	variableTable->SetVariable(key, "");

	if (m_unk0x70 != NULL) {
		delete m_unk0x70;
		m_unk0x70 = NULL;
	}
}
