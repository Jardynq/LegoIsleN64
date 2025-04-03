#include "entity_presenter.h"

#include "isle_path_actor.h"
#include "video_manager.h"
#include "misc.h"

LegoEntityPresenter::LegoEntityPresenter() {
	Init();
}

void LegoEntityPresenter::Init() {
	m_entity = NULL;
}

LegoEntityPresenter::~LegoEntityPresenter() {
	Destroy(TRUE);
}

undefined4 LegoEntityPresenter::SetEntity(LegoEntity* p_entity) {
	m_entity = p_entity;
	return 0;
}

void LegoEntityPresenter::Destroy(MxBool p_fromDestructor) {
	if (VideoManager()) {
		VideoManager()->UnregisterPresenter(*this);
	}

	Init();
}

void LegoEntityPresenter::Destroy() {
	Destroy(FALSE);
}

MxResult LegoEntityPresenter::StartAction(
	MxStreamController* p_controller,
	MxDSAction* p_action
) {
	MxResult result = MxCompositePresenter::StartAction(p_controller, p_action);

	if (VideoManager()) {
		VideoManager()->RegisterPresenter(*this);
	}

	return result;
}

void LegoEntityPresenter::ReadyTickle() {
	if (CurrentWorld()) {
		m_entity = (LegoEntity*) MxPresenter::CreateEntity("LegoEntity");
		if (m_entity) {
			m_entity->Create(*m_action);
			m_entity->SetLocation(
				m_action->GetLocation(),
				m_action->GetDirection(),
				m_action->GetUp(),
				TRUE
			);
			ParseExtra();
		}
		ProgressTickleState(e_starting);
	}
}

void LegoEntityPresenter::RepeatingTickle() {
	if (m_list.empty()) {
		EndAction();
	}
}

void LegoEntityPresenter::SetEntityLocation(
	const Vector3& p_location,
	const Vector3& p_direction,
	const Vector3& p_up
) {
	if (m_entity) {
		m_entity->SetLocation(p_location, p_direction, p_up, TRUE);
	}
}

void LegoEntityPresenter::ParseExtra() {
	MxU16 extraLength;
	char* extraData;
	m_action->GetExtra(extraLength, extraData);

	if (extraLength) {
		char extraCopy[512];
		memcpy(extraCopy, extraData, extraLength);
		extraCopy[extraLength] = '\0';

		m_entity->ParseAction(extraCopy);
	}
}
