#include "mx_streamer.h"

#include "mx_disk_stream_controller.h"
#include "mx_ds_action.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_ram_stream_controller.h"
#include "mx_stream_controller.h"

#include <algorithm>
#include <assert.h>

MxStreamer::MxStreamer() {
	NotificationManager()->Register(this);
}

MxResult MxStreamer::Create() {
	if (m_pool64.Allocate() || m_pool128.Allocate()) {
		return FAILURE;
	}

	return SUCCESS;
}

MxStreamer::~MxStreamer() {
	while (!m_controllers.empty()) {
		MxStreamController* controller = m_controllers.front();

		MxDSAction action;
		assert(controller->IsStoped(&action));

		m_controllers.pop_front();
		delete controller;
	}

	NotificationManager()->Unregister(this);
}

MxStreamController* MxStreamer::Open(const char* p_name, MxU16 p_lookupType) {
	MxStreamController* stream = NULL;

	if (GetOpenStream(p_name)) {
		goto done;
	}

	switch (p_lookupType) {
	case e_diskStream:
		stream = (MxStreamController*) new MxDiskStreamController();
		break;
	case e_RAMStream:
		log_error(
			"Ram stream is not supported, and isn't used in this codebase "
			"anyways. How did we get here?\n"
		);
		break;
	}

	if (stream == NULL) {
		goto done;
	}

	if (stream->Open(p_name) != SUCCESS ||
		AddStreamControllerToOpenList(stream) != SUCCESS) {
		delete stream;
		stream = NULL;
	}

done:
	return stream;
}

MxLong MxStreamer::Close(const char* p_name) {
	MxDSAction ds;
	ds.SetUnknown24(-2);

	for (list<MxStreamController*>::iterator it = m_controllers.begin();
		 it != m_controllers.end();
		 it++) {
		MxStreamController* c = *it;

		if (!p_name || c->GetAtom() == p_name) {
			m_controllers.erase(it);

			if (c->IsStoped(&ds)) {
				delete c;
			} else {
				NotificationManager()->Send(
					this,
					MxStreamerNotification(c_notificationStreamer, NULL, c)
				);
			}

			return SUCCESS;
		}
	}

	return FAILURE;
}

MxNotificationParam* MxStreamerNotification::Clone() const {
	return new MxStreamerNotification(m_type, m_sender, m_controller);
}

MxStreamController* MxStreamer::GetOpenStream(const char* p_name) {
	for (list<MxStreamController*>::iterator it = m_controllers.begin();
		 it != m_controllers.end();
		 it++) {
		if ((*it)->GetAtom() == p_name) {
			return *it;
		}
	}

	return NULL;
}

void MxStreamer::FUN_100b98f0(MxDSAction* p_action) {
	MxStreamController* controller =
		GetOpenStream(p_action->GetAtomId().GetInternal());
	if (controller && controller->IsA("MxDiskStreamController")) {
		((MxDiskStreamController*) controller)->FUN_100c8120(p_action);
	}
}

MxResult
MxStreamer::AddStreamControllerToOpenList(MxStreamController* p_stream) {
	list<MxStreamController*>::iterator i =
		find(m_controllers.begin(), m_controllers.end(), p_stream);

	assert(i == m_controllers.end());

	// DECOMP: Retail is missing the optimization that skips this check if
	// find() reaches the end.
	if (i == m_controllers.end()) {
		m_controllers.push_back(p_stream);
		return SUCCESS;
	}

	return FAILURE;
}

MxResult MxStreamer::StartAction(MxDSAction* p_action) {
	// TODO: MxAtomId operator== used here for NULL test. BETA10 0x1007dc20
	if (p_action == NULL || p_action->GetAtomId().GetInternal() == NULL ||
		p_action->GetObjectId() == -1) {
		return FAILURE;
	}

	MxStreamController* controller =
		GetOpenStream(p_action->GetAtomId().GetInternal());
	if (controller == NULL) {
		return FAILURE;
	}

	return controller->VTable0x20(p_action);
}

MxResult MxStreamer::DeleteObject(MxDSAction* p_dsAction) {
	MxDSAction tempAction;

	if (p_dsAction) {
		tempAction.SetObjectId(p_dsAction->GetObjectId());
		tempAction.SetAtomId(p_dsAction->GetAtomId());
		tempAction.SetUnknown24(p_dsAction->GetUnknown24());
	} else {
		tempAction.SetUnknown24(-2);
	}

	MxResult result = FAILURE;
	for (list<MxStreamController*>::iterator it = m_controllers.begin();
		 it != m_controllers.end();
		 it++) {
		// TODO: MxAtomId operator== used here for NULL test. BETA10 0x1007dc20
		if (p_dsAction->GetAtomId().GetInternal() == NULL ||
			p_dsAction->GetAtomId() == (*it)->GetAtom()) {
			tempAction.SetAtomId((*it)->GetAtom());
			result = (*it)->StopAction(&tempAction);
		}
	}

	return result;
}

MxBool MxStreamer::FUN_100b9b30(MxDSObject& p_dsObject) {
	MxStreamController* controller =
		GetOpenStream(p_dsObject.GetAtomId().GetInternal());
	if (controller) {
		return controller->IsStoped(&p_dsObject);
	}
	return TRUE;
}

MxLong MxStreamer::Notify(MxParam& p_param) {
	MxStreamerNotification& s = static_cast<MxStreamerNotification&>(p_param);

	switch (s.GetNotification()) {
	case c_notificationStreamer: {
		// DECOMP: Beta does not use a variable, but this matches retail better.
		MxStreamController* c = s.GetController();

		MxDSAction ds;
		ds.SetUnknown24(-2);

		if (c->IsStoped(&ds)) {
			delete c;
		} else {
			NotificationManager()->Send(
				this,
				MxStreamerNotification(c_notificationStreamer, NULL, c)
			);
		}

		break;
	}
	default:
		assert(0);
		break;
	}

	return 0;
}
