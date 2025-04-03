#include "mx_action_notification_param.h"

MxNotificationParam* MxStartActionNotificationParam::Clone() const {
	return new MxStartActionNotificationParam(
		c_notificationStartAction,
		this->m_sender,
		this->m_action,
		this->m_realloc
	);
}

MxNotificationParam* MxType4NotificationParam::Clone() const {
	return new MxType4NotificationParam(
		this->m_sender,
		this->m_action,
		this->m_unk0x14
	);
}
