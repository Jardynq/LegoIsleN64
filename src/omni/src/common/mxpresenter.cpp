#include "mxpresenter.h"

#include "define.h"
#include "mxactionnotificationparam.h"
#include "mxautolock.h"
#include "mxcompositepresenter.h"
#include "mxdsanim.h"
#include "mxdssound.h"
#include "mxentity.h"
#include "mxeventpresenter.h"
#include "mxflcpresenter.h"
#include "mxloopingflcpresenter.h"
#include "mxloopingmidipresenter.h"
#include "mxloopingsmkpresenter.h"
#include "mxmidipresenter.h"
#include "mxmisc.h"
#include "mxnotificationmanager.h"
#include "mxobjectfactory.h"
#include "mxomni.h"
#include "mxparam.h"
#include "mxsmkpresenter.h"
#include "mxstillpresenter.h"
#include "mxstreamer.h"
#include "mxutilities.h"
#include "mxwavepresenter.h"

#include <string.h>

void MxPresenter::Init() {
	m_currentTickleState = e_idle;
	m_action = NULL;
	m_location = MxPoint32(0, 0);
	m_displayZ = 0;
	m_compositePresenter = NULL;
	m_previousTickleStates = 0;
}

MxResult MxPresenter::StartAction(MxStreamController*, MxDSAction* p_action) {
	AUTOLOCK(m_criticalSection);

	m_action = p_action;
	m_location =
		MxPoint32(m_action->GetLocation()[0], m_action->GetLocation()[1]);
	m_displayZ = m_action->GetLocation()[2];

	ProgressTickleState(e_ready);

	return SUCCESS;
}

void MxPresenter::EndAction() {
	if (m_action == NULL) {
		return;
	}

	AUTOLOCK(m_criticalSection);

	if (!m_compositePresenter) {
		MxOmni::GetInstance()->NotifyCurrentEntity(MxEndActionNotificationParam(
			c_notificationEndAction,
			NULL,
			m_action,
			TRUE
		));
	}

	m_action = NULL;
	MxS32 previousTickleState = 1 << m_currentTickleState;
	m_previousTickleStates |= previousTickleState;
	m_currentTickleState = e_idle;
}

void MxPresenter::ParseExtra() {
	AUTOLOCK(m_criticalSection);

	MxU16 extraLength = 0;
	char* extraData = nullptr;
	m_action->GetExtra(extraLength, extraData);

	if (extraLength) {
		char extraCopy[512];
		memcpy(extraCopy, extraData, extraLength);
		extraCopy[extraLength] = '\0';

		char worldValue[512];
		if (KeyValueStringParse(worldValue, g_strWORLD, extraCopy)) {
			char* token = strtok(worldValue, g_parseExtraTokens);
			char buf[256];
			strcpy(buf, token);

			token = strtok(NULL, g_parseExtraTokens);
			MxS32 val = token ? atoi(token) : 0;
			MxEntity* result =
				MxOmni::GetInstance()->AddToWorld(buf, val, this);

			m_action->SetFlags(m_action->GetFlags() | MxDSAction::c_world);

			if (result) {
				SendToCompositePresenter(MxOmni::GetInstance());
			}
		}
	}
}

void MxPresenter::SendToCompositePresenter(MxOmni* p_omni) {
	if (m_compositePresenter) {
		AUTOLOCK(m_criticalSection);

		NotificationManager()->Send(
			m_compositePresenter,
			MxNotificationParam(c_notificationPresenter, this)
		);
		m_action->SetOrigin(p_omni ? p_omni : MxOmni::GetInstance());
		m_compositePresenter = NULL;
	}
}

MxResult MxPresenter::Tickle() {
	AUTOLOCK(m_criticalSection);

	switch (m_currentTickleState) {
	case e_ready:
		ReadyTickle();

		if (m_currentTickleState != e_starting) {
			break;
		}
	case e_starting:
		StartingTickle();

		if (m_currentTickleState != e_streaming) {
			break;
		}
	case e_streaming:
		StreamingTickle();

		if (m_currentTickleState != e_repeating) {
			break;
		}
	case e_repeating:
		RepeatingTickle();

		if (m_currentTickleState != e_freezing) {
			break;
		}
	case e_freezing:
		FreezingTickle();

		if (m_currentTickleState != e_done) {
			break;
		}
	case e_done:
		DoneTickle();
	default:
		break;
	}

	return SUCCESS;
}

void MxPresenter::Enable(MxBool p_enable) {
	if (m_action && IsEnabled() != p_enable) {
		MxU32 flags = m_action->GetFlags();

		if (p_enable) {
			m_action->SetFlags(flags | MxDSAction::c_enabled);
		} else {
			m_action->SetFlags(flags & ~MxDSAction::c_enabled);
		}
	}
}

const char* PresenterNameDispatch(const MxDSAction& p_action) {
	const char* name = p_action.GetSourceName();
	MxS32 format = 0;

	if (!name || strlen(name) == 0) {
		switch (p_action.GetType()) {
		case MxDSObject::e_anim:
			format = ((MxDSAnim&) p_action).GetMediaFormat();
			switch (format) {
			case FOURCC(' ', 'F', 'L', 'C'):
				name = !p_action.IsLooping()
						   ? MxFlcPresenter::HandlerClassName()
						   : MxLoopingFlcPresenter::HandlerClassName();
				break;
			case FOURCC(' ', 'S', 'M', 'K'):
				name = !p_action.IsLooping()
						   ? MxSmkPresenter::HandlerClassName()
						   : MxLoopingSmkPresenter::HandlerClassName();
				break;
			}
			break;

		case MxDSObject::e_sound:
			format = ((MxDSSound&) p_action).GetMediaFormat();
			switch (format) {
			case FOURCC(' ', 'M', 'I', 'D'):
				name = !p_action.IsLooping()
						   ? MxMIDIPresenter::HandlerClassName()
						   : MxLoopingMIDIPresenter::HandlerClassName();
				break;
			case FOURCC(' ', 'W', 'A', 'V'):
				name = MxWavePresenter::HandlerClassName();
				break;
			}
			break;

		case MxDSObject::e_serialAction:
		case MxDSObject::e_parallelAction:
		case MxDSObject::e_selectAction:
			name = MxCompositePresenter::HandlerClassName();
			break;

		case MxDSObject::e_event:
			name = MxEventPresenter::HandlerClassName();
			break;

		case MxDSObject::e_still:
			name = MxStillPresenter::HandlerClassName();
			break;
		case MxDSObject::e_object:
		case MxDSObject::e_action:
		case MxDSObject::e_mediaAction:
		case MxDSObject::e_multiAction:
		case MxDSObject::e_objectAction:
			break;
		}
	}

	return name;
}

MxEntity* MxPresenter::CreateEntity(const char* p_defaultName) {
	// create an object from LegoObjectFactory based on OBJECT: value in extra
	// data. If that is missing, p_defaultName is used

	char objectName[512];
	strcpy(objectName, p_defaultName);

	MxU16 extraLength = 0;
	char* extraData = nullptr;
	m_action->GetExtra(extraLength, extraData);

	if (extraLength) {
		char extraCopy[512];
		memcpy(extraCopy, extraData, extraLength);
		extraCopy[extraLength] = '\0';
		KeyValueStringParse(objectName, g_strOBJECT, extraCopy);
	}

	return (MxEntity*) ObjectFactory()->Create(objectName);
}

MxBool MxPresenter::IsEnabled() {
	return m_action && m_action->GetFlags() & MxDSAction::c_enabled;
}
