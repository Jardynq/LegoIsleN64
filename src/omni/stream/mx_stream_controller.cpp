#include "mx_stream_controller.h"

#include "mx_ds_multi_action.h"
#include "mx_ds_streaming_action.h"
#include "mx_misc.h"
#include "mx_next_action_data_start.h"
#include "mx_stream_chunk.h"
#include "mx_stream_provider.h"
#include "mx_timer.h"
#include "mx_utilities.h"

MxStreamController::MxStreamController() {
	m_provider = NULL;
	m_unk0x2c = NULL;
	m_action0x60 = NULL;
}

MxStreamController::~MxStreamController() {
	MxDSSubscriber* subscriber = nullptr;
	while (m_subscribers.PopFront(subscriber)) {
		delete subscriber;
	}

	MxDSObject* action = nullptr;
	while (m_unk0x3c.PopFront(action)) {
		delete action;
	}

	if (m_provider) {
		MxStreamProvider* provider = m_provider;
		m_provider = NULL;
		MxDSAction action;
		provider->VTable0x20(&action);
		delete provider;
	}

	if (m_unk0x2c) {
		delete m_unk0x2c;
		m_unk0x2c = NULL;
	}

	while (m_unk0x54.PopFront(action)) {
		delete action;
	}
}

MxResult MxStreamController::Open(const char* p_filename) {
	char sourceName[256];

	MakeSourceName(sourceName, p_filename);
	m_atom = MxAtomId(sourceName, e_lowerCase2);
	return SUCCESS;
}

void MxStreamController::AddSubscriber(MxDSSubscriber* p_subscriber) {
	m_subscribers.PushBack(p_subscriber);
}

void MxStreamController::RemoveSubscriber(MxDSSubscriber* p_subscriber) {
	m_subscribers.Remove(p_subscriber);
}

MxResult MxStreamController::VTable0x20(MxDSAction* p_action) {
	MxResult result = 0;
	MxU32 offset = 0;

	MxS32 objectId = p_action->GetObjectId();
	MxStreamProvider* provider = m_provider;

	if ((MxS32) provider->GetLengthInDWords() > objectId) {
		offset = provider->GetBufferForDWords()[objectId];
	}

	if (offset) {
		result = VTable0x2c(p_action, offset);
	} else {
		result = FAILURE;
	}

	return result;
}

MxResult MxStreamController::StopAction(MxDSAction* p_action) {
	DeleteAction(p_action);
	m_action0x60 = (MxDSAction*) m_unk0x54.FindAndErase(p_action);

	if (m_action0x60 == NULL) {
		return FAILURE;
	} else {
		p_action->SetUnknown24(m_action0x60->GetUnknown24());
		p_action->SetObjectId(m_action0x60->GetObjectId());
		return FUN_100c1f00(m_action0x60);
	}
}

MxResult MxStreamController::FUN_100c1800(MxDSAction* p_action, MxU32 p_val) {
	MxNextActionDataStart* dataActionStart = new MxNextActionDataStart(
		p_action->GetObjectId(),
		p_action->GetUnknown24(),
		p_val
	);
	if (dataActionStart == NULL) {
		return FAILURE;
	}

	m_nextActionList.PushBack(dataActionStart);
	return SUCCESS;
}

MxResult
MxStreamController::FUN_100c1a00(MxDSAction* p_action, MxU32 p_offset) {
	if (p_action->GetUnknown24() == -1) {
		MxS16 newUnknown24 = -1;

		// These loops might be a template function in the list classes
		for (MxDSObjectList::iterator it = m_unk0x54.begin();
			 it != m_unk0x54.end();
			 it++) {
			MxDSObject* action = *it;

			if (action->GetObjectId() == p_action->GetObjectId()) {
				newUnknown24 = Max(newUnknown24, action->GetUnknown24());
			}
		}

		if (newUnknown24 == -1) {
			for (MxDSObjectList::iterator it = m_unk0x3c.begin();
				 it != m_unk0x3c.end();
				 it++) {
				MxDSObject* action = *it;

				if (action->GetObjectId() == p_action->GetObjectId()) {
					newUnknown24 = Max(newUnknown24, action->GetUnknown24());
				}
			}

			if (newUnknown24 == -1) {
				for (MxDSSubscriberList::iterator it = m_subscribers.begin();
					 it != m_subscribers.end();
					 it++) {
					MxDSSubscriber* subscriber = *it;

					if (subscriber->GetObjectId() == p_action->GetObjectId()) {
						newUnknown24 =
							Max(newUnknown24, subscriber->GetUnknown48());
					}
				}
			}
		}

		p_action->SetUnknown24(newUnknown24 + 1);
	} else {
		if (m_unk0x3c.Find(p_action)) {
			return FAILURE;
		}
	}

	MxDSStreamingAction* streamingAction =
		new MxDSStreamingAction(*p_action, p_offset);

	if (!streamingAction) {
		return FAILURE;
	}

	MxU32 fileSize = m_provider->GetFileSize();
	streamingAction->SetBufferOffset(fileSize * (p_offset / fileSize));
	streamingAction->SetObjectId(p_action->GetObjectId());

	MxLong time = Timer()->GetTime();
	streamingAction->SetUnknown90(time);

	m_unk0x3c.PushBack(streamingAction);
	return SUCCESS;
}

MxResult
MxStreamController::VTable0x2c(MxDSAction* p_action, MxU32 p_bufferval) {
	if (FUN_100c1a00(p_action, p_bufferval) != SUCCESS) {
		return FAILURE;
	}

	return FUN_100c1800(
		p_action,
		(p_bufferval / m_provider->GetFileSize()) * m_provider->GetFileSize()
	);
}

MxResult MxStreamController::DeleteAction(MxDSAction* p_action) {
	MxResult result = FAILURE;
	MxDSObject* action = m_unk0x3c.FindAndErase(p_action);

	if (action != NULL) {
		MxNextActionDataStart* data = m_nextActionList.FindAndErase(
			action->GetObjectId(),
			action->GetUnknown24()
		);
		delete action;
		delete data;
		result = SUCCESS;
	}

	return result;
}

MxResult MxStreamController::InsertActionToList54(MxDSAction* p_action) {
	MxDSAction* action = p_action->Clone();

	if (action == NULL) {
		return FAILURE;
	} else {
		m_unk0x54.PushBack(action);
		return SUCCESS;
	}
}

MxPresenter* MxStreamController::FUN_100c1e70(MxDSAction& p_action) {
	MxPresenter* result = NULL;

	if (p_action.GetObjectId() != -1) {
		MxDSObject* action = m_unk0x3c.Find(&p_action);
		if (action != NULL) {
			result = action->GetUnknown28();
		}
	}

	return result;
}

MxResult MxStreamController::FUN_100c1f00(MxDSAction* p_action) {
	MxU32 objectId = p_action->GetObjectId();
	MxStreamChunk* chunk = new MxStreamChunk;

	if (!chunk) {
		return FAILURE;
	}

	chunk->SetChunkFlags(DS_CHUNK_BIT3);
	chunk->SetObjectId(objectId);

	if (chunk->SendChunk(m_subscribers, FALSE, p_action->GetUnknown24()) !=
		SUCCESS) {
		delete chunk;
	}

	if (p_action->IsA("MxDSMultiAction")) {
		MxDSActionList* actions =
			((MxDSMultiAction*) p_action)->GetActionList();
		MxDSActionListCursor cursor(actions);
		MxDSAction* action = nullptr;

		while (cursor.Next(action)) {
			if (FUN_100c1f00(action) != SUCCESS) {
				return FAILURE;
			}
		}
	}

	return SUCCESS;
}

MxNextActionDataStart*
MxStreamController::FindNextActionDataStartFromStreamingAction(
	MxDSStreamingAction* p_action
) {
	return m_nextActionList.Find(
		p_action->GetObjectId(),
		p_action->GetUnknown24()
	);
}

MxBool MxStreamController::IsStoped(MxDSObject* p_obj) {
	MxDSSubscriber* subscriber = m_subscribers.Find(p_obj);

	if (subscriber) {
		return FALSE;
	}

	if (p_obj->IsA("MxDSMultiAction")) {
		MxDSActionListCursor cursor(((MxDSMultiAction*) p_obj)->GetActionList()
		);
		MxDSAction* action = nullptr;

		while (cursor.Next(action)) {
			if (!IsStoped(action)) {
				return FALSE;
			}
		}
	}

	return TRUE;
}

MxNextActionDataStart*
MxNextActionDataStartList::Find(MxU32 p_id, MxS16 p_value) {
	for (iterator it = begin(); it != end(); it++) {
		if (p_id == (*it)->GetObjectId() && p_value == (*it)->GetUnknown24()) {
			return *it;
		}
	}

	return NULL;
}

MxNextActionDataStart*
MxNextActionDataStartList::FindAndErase(MxU32 p_id, MxS16 p_value) {
	MxNextActionDataStart* match = NULL;

	for (iterator it = begin(); it != end(); it++) {
		if (p_id == (*it)->GetObjectId() &&
			(p_value == -2 || p_value == (*it)->GetUnknown24())) {
			match = *it;
			erase(it);
			break;
		}
	}

	return match;
}
