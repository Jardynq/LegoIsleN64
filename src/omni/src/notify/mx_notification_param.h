#ifndef MXNOTIFICATIONPARAM_H
#define MXNOTIFICATIONPARAM_H

#include "mx_param.h"

class MxCore;

// Several of those should be defined in LegoOmni
enum NotificationId {
	c_notificationType0 = 0,
	c_notificationStartAction = 1, // 100dc210:100d8350
	c_notificationEndAction = 2,   // 100d8358:100d8350
	c_notificationType4 = 4,       // 100dc208:100d8350
	c_notificationPresenter = 5,
	c_notificationStreamer = 6,   // 100dc760
	c_notificationKeyPress = 7,   // 100d6aa0
	c_notificationButtonUp = 8,   // 100d6aa0
	c_notificationButtonDown = 9, // 100d6aa0
	c_notificationMouseMove = 10, // 100d6aa0
	c_notificationClick = 11,     // 100d6aa0
	c_notificationDragStart = 12,
	c_notificationDrag = 13,
	c_notificationDragEnd = 14,
	c_notificationTimer = 15, // 100d6aa0
	c_notificationControl = 17,
	c_notificationEndAnim = 18,    // 100d7e80
	c_notificationPathStruct = 19, // 100d6230
	c_notificationType20 = 20,
	c_notificationNewPresenter = 21,
	c_notificationType22 = 22,
	c_notificationType23 = 23,
	c_notificationTransitioned = 24
};

class MxNotificationParam : public MxParam {
public:
	MxNotificationParam() : m_type(c_notificationType0), m_sender(NULL) {}

	MxNotificationParam(NotificationId p_type, MxCore* p_sender)
		: MxParam(), m_type(p_type), m_sender(p_sender) {}

	virtual MxNotificationParam* Clone() const {
		return new MxNotificationParam(m_type, m_sender);
	}

	NotificationId GetNotification() const { return m_type; }

	MxCore* GetSender() const { return m_sender; }

	void SetNotification(NotificationId p_type) { m_type = p_type; }

	void SetSender(MxCore* p_sender) { m_sender = p_sender; }

protected:
	NotificationId m_type;
	MxCore* m_sender;
};

// MxNotificationParam::`scalar deleting destructor'

// MxNotificationParam::~MxNotificationParam

#endif // MXNOTIFICATIONPARAM_H
