#include "building_entity.h"

#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_notification_param.h"

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
