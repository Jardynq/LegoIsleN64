#include "mxactionnotificationparam.h"


// FUNCTION: LEGO1 0x100b0300
MxNotificationParam* MxStartActionNotificationParam::Clone() const {
	return new MxStartActionNotificationParam(
		c_notificationStartAction,
		this->m_sender,
		this->m_action,
		this->m_realloc
	);
}

// FUNCTION: LEGO1 0x100b04f0
MxNotificationParam* MxType4NotificationParam::Clone() const {
	return new MxType4NotificationParam(this->m_sender, this->m_action, this->m_unk0x14);
}
