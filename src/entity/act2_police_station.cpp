#include "act2_police_station.h"

#include "world.h"
#include "misc.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_notification_param.h"

MxLong Act2PoliceStation::Notify(MxParam& p_param) {
	MxNotificationParam& param = (MxNotificationParam&) p_param;

	if (param.GetNotification() == c_notificationClick) {
		MxNotificationParam param(c_notificationType23, NULL);
		NotificationManager()->Send(CurrentWorld(), param);
		return 1;
	}

	return 0;
}
