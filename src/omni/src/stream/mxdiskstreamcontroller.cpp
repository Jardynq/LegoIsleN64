#include "mxdiskstreamcontroller.h"

#include "mxactionnotificationparam.h"
#include "mxautolock.h"
#include "mxdiskstreamprovider.h"
#include "mxdsstreamingaction.h"
#include "mxmisc.h"
#include "mxomni.h"
#include "mxticklemanager.h"

#include <assert.h>

MxDiskStreamController::MxDiskStreamController() {
	m_unk0x8c = 0;
}

MxDiskStreamController::~MxDiskStreamController() {
	AUTOLOCK(m_criticalSection);

	m_unk0xc4 = FALSE;
	m_unk0x70 = FALSE;

	if (m_provider) {
		MxDSAction action;
		m_provider->VTable0x20(&action);
	}

	assert(m_subscribers.size() == 0);

	MxDSObject* object;
	while (m_unk0x3c.PopFront(object)) {
		delete object;
	}

	if (m_provider) {
		delete m_provider;
		m_provider = NULL;
	}

	FUN_100c8720();

	while (m_list0x80.PopFront(object)) {
		FUN_100c7cb0((MxDSStreamingAction*) object);
	}

	while (m_list0x64.PopFront(object)) {
		FUN_100c7cb0((MxDSStreamingAction*) object);
	}

	while (!m_list0x74.empty()) {
		MxDSBuffer* buffer = m_list0x74.front();
		m_list0x74.pop_front();
		FUN_100c7ce0(buffer);
	}

	TickleManager()->UnregisterClient(this);
}

MxResult MxDiskStreamController::Open(const char* p_filename) {
	AUTOLOCK(m_criticalSection);
	MxResult result = MxStreamController::Open(p_filename);

	if (result != SUCCESS) {
		goto done;
	}

	m_provider = new MxDiskStreamProvider();
	if (m_provider == NULL) {
		result = FAILURE;
		goto done;
	}

	result = m_provider->SetResourceToGet(this);
	if (result != SUCCESS) {
		delete m_provider;
		m_provider = NULL;
		goto done;
	}

	TickleManager()->RegisterClient(this, 10);

done:
	return result;
}

MxResult MxDiskStreamController::VTable0x18(undefined4, undefined4) {
	return SUCCESS;
}

MxResult MxDiskStreamController::FUN_100c7890(MxDSStreamingAction* p_action) {
	AUTOLOCK(m_criticalSection);
	if (p_action == NULL) {
		return FAILURE;
	}

	m_list0x80.PushBack(p_action);
	FUN_100c7970();
	return SUCCESS;
}

MxResult MxDiskStreamController::VTable0x34(undefined4) {
	return FAILURE;
}

void MxDiskStreamController::FUN_100c7970() {
	// Empty
}

void MxDiskStreamController::FUN_100c7980() {
	MxDSBuffer* buffer;
	MxDSStreamingAction* action = NULL;

	{
		AUTOLOCK(m_criticalSection);

		if (m_unk0x3c.size() && m_unk0x8c < m_provider->GetStreamBuffersNum()) {
			buffer = new MxDSBuffer();

			if (buffer->AllocateBuffer(
					m_provider->GetFileSize(),
					MxDSBuffer::e_chunk
				) != SUCCESS) {
				if (buffer) {
					delete buffer;
				}
				return;
			}

			action = VTable0x28();
			if (!action) {
				if (buffer) {
					delete buffer;
				}
				return;
			}

			action->SetUnknowna0(buffer);
			m_unk0x8c++;
		}
	}

	if (action) {
		((MxDiskStreamProvider*) m_provider)->FUN_100d1780(action);
	}
}

MxDSStreamingAction* MxDiskStreamController::VTable0x28() {
	AUTOLOCK(m_criticalSection);
	MxDSObject* oldAction;

	assert(m_provider);
	MxDSStreamingAction* request = NULL;
	MxU32 filesize = m_provider->GetFileSize();

	if (!m_unk0x3c.PopFront(oldAction)) {
		goto done;
	}

	request = new MxDSStreamingAction((MxDSStreamingAction&) *oldAction);
	assert(request);

	if (!request) {
		goto done;
	}

	((MxDSStreamingAction*) oldAction)
		->SetUnknown94(request->GetBufferOffset() + filesize);
	((MxDSStreamingAction*) oldAction)
		->SetBufferOffset(((MxDSStreamingAction*) oldAction)->GetUnknown94());
	m_unk0x3c.PushBack(oldAction);

done:
	return request;
}

MxResult MxDiskStreamController::VTable0x30(MxDSAction* p_action) {
	AUTOLOCK(m_criticalSection);
	MxResult result = MxStreamController::VTable0x30(p_action);

	MxDSStreamingAction* item;
	while (TRUE) {
		item = (MxDSStreamingAction*) m_list0x90.FindAndErase(p_action);
		if (item == NULL) {
			break;
		}
		FUN_100c7cb0(item);
	}

	while (TRUE) {
		item = (MxDSStreamingAction*) m_list0x64.FindAndErase(p_action);
		if (item == NULL) {
			break;
		}
		FUN_100c7cb0(item);
	}

	return result;
}

void MxDiskStreamController::FUN_100c7cb0(MxDSStreamingAction* p_action) {
	if (p_action->GetUnknowna0()) {
		FUN_100c7ce0(p_action->GetUnknowna0());
	}
	p_action->SetUnknowna0(NULL);
	delete p_action;
}

void MxDiskStreamController::FUN_100c7ce0(MxDSBuffer* p_buffer) {
	switch (p_buffer->GetMode()) {
	case MxDSBuffer::e_chunk:
		m_unk0x8c--;
	case MxDSBuffer::e_allocate:
	case MxDSBuffer::e_unknown:
		delete p_buffer;
		break;
	}
}

MxResult MxDiskStreamController::FUN_100c7d10() {
	AUTOLOCK(m_criticalSection);
	MxDSStreamingAction* action = FUN_100c7db0();

	if (!action) {
		return FAILURE;
	}

	if (FUN_100c8360(action) != SUCCESS) {
		VTable0x24(action);
		FUN_100c7cb0(action);
		return FAILURE;
	}

	return SUCCESS;
}

MxDSStreamingAction* MxDiskStreamController::FUN_100c7db0() {
	AUTOLOCK(m_criticalSection);

	for (MxNextActionDataStartList::iterator it = m_nextActionList.begin();
		 it != m_nextActionList.end();
		 it++) {
		MxNextActionDataStart* data = *it;

		for (MxDSObjectList::iterator it2 = m_list0x64.begin();
			 it2 != m_list0x64.end();
			 it2++) {
			MxDSStreamingAction* streamingAction = (MxDSStreamingAction*) *it2;

			if (streamingAction->GetObjectId() == data->GetObjectId() &&
				streamingAction->GetUnknown24() == data->GetUnknown24() &&
				streamingAction->GetBufferOffset() == data->GetData()) {
				m_nextActionList.erase(it);

				data->SetData(m_provider->GetFileSize() + data->GetData());
				m_nextActionList.PushBack(data);

				m_list0x64.erase(it2);
				return streamingAction;
			}
		}
	}

	return NULL;
}

void MxDiskStreamController::FUN_100c7f40(MxDSStreamingAction* p_streamingaction
) {
	AUTOLOCK(m_criticalSection);
	if (p_streamingaction) {
		m_list0x64.PushBack(p_streamingaction);
	}
}

MxResult MxDiskStreamController::VTable0x20(MxDSAction* p_action) {
	AUTOLOCK(m_criticalSection);
	MxDSStreamingAction* entry = (MxDSStreamingAction*) m_list0x80.Find(p_action
	); // TODO: is this a seperate class?

	if (entry) {
		MxDSStreamingAction* action = new MxDSStreamingAction(*p_action, 0);
		action->SetUnknown28(entry->GetUnknown28());
		action->SetUnknown84(entry->GetUnknown84());
		action->SetOrigin(entry->GetOrigin());
		action->SetUnknowna0(entry->GetUnknowna4());

		FUN_100c7f40(action);

		if (VTable0x2c(p_action, entry->GetUnknown94()) != SUCCESS) {
			return FAILURE;
		}
	} else if (MxStreamController::VTable0x20(p_action) != SUCCESS) {
		return FAILURE;
	}

	m_unk0x70 = TRUE;
	m_unk0xc4 = TRUE;
	return SUCCESS;
}

void MxDiskStreamController::FUN_100c8120(MxDSAction* p_action) {
	VTable0x30(p_action);

	if (m_provider) {
		m_provider->VTable0x20(p_action);
	}

	while (TRUE) {
		MxDSObject* found = m_unk0x54.FindAndErase(p_action);
		if (!found) {
			break;
		}
		delete found;
	}
}

MxResult MxDiskStreamController::VTable0x24(MxDSAction* p_action) {
	AUTOLOCK(m_criticalSection);
	if (m_unk0x54.Find(p_action) == NULL) {
		if (VTable0x30(p_action) == SUCCESS) {
			MxOmni::GetInstance()->NotifyCurrentEntity(
				MxEndActionNotificationParam(
					c_notificationEndAction,
					NULL,
					p_action,
					TRUE
				)
			);
		}
	}

	MxDSAction action;
	if (m_provider) {
		m_provider->VTable0x20(p_action);
	}

	do {
		if (m_action0x60 != NULL) {
			delete m_action0x60;
			m_action0x60 = NULL;
		}

		action = *p_action;
		MxStreamController::VTable0x24(&action);
	} while (m_action0x60 != NULL);

	if (m_unk0x3c.empty()) {
		m_unk0x70 = FALSE;
		m_unk0xc4 = FALSE;
	}

	return SUCCESS;
}

MxResult MxDiskStreamController::FUN_100c8360(MxDSStreamingAction* p_action) {
	AUTOLOCK(m_criticalSection);
	MxDSBuffer* buffer = p_action->GetUnknowna0();
	MxDSStreamingAction* action2 =
		(MxDSStreamingAction*) m_list0x90.FindAndErase(p_action);
	buffer->FUN_100c6f80(
		p_action->GetUnknown94() - p_action->GetBufferOffset()
	);
	buffer->FUN_100c67b0(this, p_action, &action2);

	if (buffer->GetRefCount()) {
		p_action->SetUnknowna0(NULL);
		InsertToList74(buffer);
	}

	if (action2) {
		if (action2->GetUnknowna0() == NULL) {
			FUN_100c7cb0(action2);
		} else {
			if (action2->GetObjectId() == -1) {
				action2->SetObjectId(p_action->GetObjectId());
			}

			m_list0x90.PushBack(action2);
		}
	}

	FUN_100c7cb0(p_action);
	return SUCCESS;
}

void MxDiskStreamController::InsertToList74(MxDSBuffer* p_buffer) {
	AUTOLOCK(m_criticalSection);
	m_list0x74.push_back(p_buffer);
}

void MxDiskStreamController::FUN_100c8540() {
	AUTOLOCK(m_criticalSection);
	for (list<MxDSBuffer*>::iterator it = m_list0x74.begin();
		 it != m_list0x74.end();) {
		MxDSBuffer* buf = *it;
		if (buf->GetRefCount() == 0) {
			m_list0x74.erase(it++);
			FUN_100c7ce0(buf);
		} else {
			it++;
		}
	}

	if (m_nextActionList.empty()) {
		while (!m_list0x64.empty()) {
			MxDSStreamingAction* action =
				(MxDSStreamingAction*) m_list0x64.front();
			m_list0x64.pop_front();
			FUN_100c7cb0(action);
		}
	}
}

MxResult MxDiskStreamController::Tickle() {
	if (m_unk0xc4) {
		FUN_100c7d10();
	}

	FUN_100c8540();
	FUN_100c8720();

	if (m_unk0x70) {
		FUN_100c7980();
	}

	return SUCCESS;
}

void MxDiskStreamController::FUN_100c8670(MxDSStreamingAction* p_streamingAction
) {
	AUTOLOCK(m_critical9c);
	m_list0xb8.push_back(p_streamingAction);
}

void MxDiskStreamController::FUN_100c8720() {
	AUTOLOCK(m_critical9c);

	MxDSStreamingAction* action;
	while (!m_list0xb8.empty()) {
		action = (MxDSStreamingAction*) m_list0xb8.front();
		m_list0xb8.pop_front();
		FUN_100c7cb0(action);
	}
}
