#include "path_presenter.h"

#include "define.h"
#include "path_controller.h"
#include "video_manager.h"
#include "world.h"
#include "misc.h"
#include "mxautolock.h"
#include "mx_ds_subscriber.h"
#include "mx_utilities.h"

LegoPathPresenter::LegoPathPresenter() {
	Init();
}

void LegoPathPresenter::Init() {
}

LegoPathPresenter::~LegoPathPresenter() {
	Destroy(TRUE);
}

MxResult LegoPathPresenter::AddToManager() {
	MxResult status = FAILURE;

	if (VideoManager()) {
		VideoManager()->RegisterPresenter(*this);
		status = SUCCESS;
	}

	return status;
}

void LegoPathPresenter::Destroy(MxBool p_fromDestructor) {
	if (VideoManager()) {
		VideoManager()->UnregisterPresenter(*this);
	}

	{
		AUTOLOCK(m_criticalSection);
		Init();
	}

	if (!p_fromDestructor) {
		MxMediaPresenter::Destroy(FALSE);
	}
}

void LegoPathPresenter::Destroy() {
	Destroy(FALSE);
}

void LegoPathPresenter::ReadyTickle() {
	LegoWorld* world = CurrentWorld();

	if (world) {
		MxStreamChunk* chunk = m_subscriber->PopData();

		if (chunk) {
			LegoPathController* controller = new LegoPathController();

			if (controller == NULL) {
				EndAction();
			} else {
				ParseExtra();

				controller->Create(
					chunk->GetData(),
					m_action->GetLocation(),
					m_trigger
				);
				world->AddPath(controller);

				m_subscriber->FreeDataChunk(chunk);
				ProgressTickleState(MxPresenter::e_starting);
			}
		}
	}
}

void LegoPathPresenter::StreamingTickle() {
	MxStreamChunk* chunk = m_subscriber->PopData();

	if (chunk) {
		if (chunk->GetChunkFlags() & DS_CHUNK_END_OF_STREAM) {
			ProgressTickleState(e_repeating);
		}

		m_subscriber->FreeDataChunk(chunk);
	}
}

void LegoPathPresenter::RepeatingTickle() {
	if (this->m_action->GetDuration() == -1) {
		return;
	}

	EndAction();
}

void LegoPathPresenter::ParseExtra() {
	MxU16 extraLength;
	char* extraData;
	m_action->GetExtra(extraLength, extraData);

	if (extraLength) {
		char extraCopy[256], output[256];
		memcpy(extraCopy, extraData, extraLength);
		extraCopy[extraLength] = '\0';

		strupr(extraCopy);

		if (KeyValueStringParse(output, g_strTRIGGERS_SOURCE, extraCopy) !=
			FALSE) {
			m_trigger = MxAtomId(output, e_lowerCase2);
		}
	}
}
