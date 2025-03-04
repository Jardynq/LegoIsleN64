#include "buildingentity.h"

#include "mxmisc.h"
#include "mxnotificationmanager.h"
#include "mxnotificationparam.h"

BuildingEntity::BuildingEntity() {
	NotificationManager()->Register(this);
}

BuildingEntity::~BuildingEntity() {
	NotificationManager()->Unregister(this);
}

MxLong BuildingEntity::Notify(MxParam& p_param) {
	MxNotificationParam& param = (MxNotificationParam&) p_param;

	if (param.GetNotification() == c_notificationClick) {
		return HandleClick((LegoEventNotificationParam&) p_param);
	}

	return 0;
}
