#include "mx_media_presenter.h"

#include "mx_action_notification_param.h"
#include "mx_composite_presenter.h"
#include "mx_ds_subscriber.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_timer.h"

void MxMediaPresenter::Init() {
}

void MxMediaPresenter::Destroy(MxBool p_fromDestructor) {
	Init();
	if (!p_fromDestructor) {
		MxPresenter::Destroy();
	}
}

MxResult MxMediaPresenter::StartAction(
	MxStreamController* p_controller,
	MxDSAction* p_action
) {
	MxResult result = FAILURE;

	if (MxPresenter::StartAction(p_controller, p_action) == SUCCESS) {
		if (m_action->GetFlags() & MxDSAction::c_looping) {
		}

		result = SUCCESS;
	}

	return result;
}

void MxMediaPresenter::EndAction() {
	if (!m_action) {
		return;
	}

	if (m_action->GetFlags() & MxDSAction::c_world &&
		(!m_compositePresenter || !m_compositePresenter->VTable0x64(2))) {
		MxPresenter::Enable(FALSE);
		SetTickleState(e_idle);
	} else {
		MxDSAction* action = m_action;
		MxPresenter::EndAction();

		if (action && action->GetOrigin()) {
			NotificationManager()->Send(
				action->GetOrigin(),
				MxEndActionNotificationParam(
					c_notificationEndAction,
					this,
					action,
					FALSE
				)
			);
		}
	}
}

MxResult MxMediaPresenter::Tickle() {
	return MxPresenter::Tickle();
}

void MxMediaPresenter::StreamingTickle() {
}

void MxMediaPresenter::RepeatingTickle() {
	if (IsEnabled()) {
		if (m_action->GetElapsedTime() >=
			m_action->GetStartTime() + m_action->GetDuration()) {
			ProgressTickleState(e_freezing);
		}
	}
}

void MxMediaPresenter::DoneTickle() {
	ProgressTickleState(e_idle);
	EndAction();
}

void MxMediaPresenter::Enable(MxBool p_enable) {
	if (IsEnabled() != p_enable) {
		MxPresenter::Enable(p_enable);

		if (p_enable) {
			MxLong time = Timer()->GetTime();
			m_action->SetUnknown90(time);
			SetTickleState(e_repeating);
		} else {
			SetTickleState(e_done);
		}
	}
}
