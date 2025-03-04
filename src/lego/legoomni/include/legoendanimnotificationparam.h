#ifndef LEGOENDANIMNOTIFICATIONPARAM_H
#define LEGOENDANIMNOTIFICATIONPARAM_H

#include "mxnotificationparam.h"

class LegoEndAnimNotificationParam : public MxNotificationParam {
public:
	LegoEndAnimNotificationParam(
		NotificationId p_type,
		MxCore* p_sender,
		MxU32 p_index
	)
		: MxNotificationParam(p_type, p_sender), m_index(p_index) {}

	MxNotificationParam* Clone() const override {
		return new LegoEndAnimNotificationParam(m_type, m_sender, m_index);
	}

	MxU32 GetIndex() { return m_index; }

protected:
	MxU32 m_index;
};

// LegoEndAnimNotificationParam::`scalar deleting destructor'

// LegoEndAnimNotificationParam::~LegoEndAnimNotificationParam

#endif // LEGOENDANIMNOTIFICATIONPARAM_H
