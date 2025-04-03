#include "mx_ds_serial_action.h"

#include "mx_ds_media_action.h"

MxDSSerialAction::MxDSSerialAction() {
	this->SetType(e_serialAction);
	this->m_cursor = new MxDSActionListCursor(this->m_actions);
	this->m_unk0xa0 = 0;
}

void MxDSSerialAction::SetDuration(MxLong p_duration) {
	this->m_duration = p_duration;
}

MxDSSerialAction::~MxDSSerialAction() {
	if (this->m_cursor) {
		delete this->m_cursor;
	}

	this->m_cursor = NULL;
}

void MxDSSerialAction::CopyFrom(MxDSSerialAction& p_dsSerialAction) {
}

MxDSSerialAction& MxDSSerialAction::operator=(MxDSSerialAction& p_dsSerialAction
) {
	if (this == &p_dsSerialAction) {
		return *this;
	}

	MxDSMultiAction::operator=(p_dsSerialAction);
	this->CopyFrom(p_dsSerialAction);
	return *this;
}

MxDSAction* MxDSSerialAction::Clone() {
	MxDSSerialAction* clone = new MxDSSerialAction();

	if (clone) {
		*clone = *this;
	}

	return clone;
}

MxLong MxDSSerialAction::GetDuration() {
	if (this->m_duration) {
		return this->m_duration;
	}

	MxDSActionListCursor cursor(this->m_actions);
	MxDSAction* action;

	while (cursor.Next(action)) {
		if (!action) {
			continue;
		}

		this->m_duration += action->GetDuration() + action->GetStartTime();

		if (action->IsA("MxDSMediaAction")) {
			MxLong sustainTime = ((MxDSMediaAction*) action)->GetSustainTime();

			if (sustainTime && sustainTime != -1) {
				this->m_duration += sustainTime;
			}
		}
	}

	return this->m_duration;
}
