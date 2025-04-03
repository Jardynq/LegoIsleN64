#include "mx_ds_event.h"

MxDSEvent::MxDSEvent() {
	this->SetType(e_event);
}

MxDSEvent::~MxDSEvent() {
}

void MxDSEvent::CopyFrom(MxDSEvent& p_dsEvent) {
}

MxDSEvent& MxDSEvent::operator=(MxDSEvent& p_dsEvent) {
	if (this == &p_dsEvent) {
		return *this;
	}

	MxDSMediaAction::operator=(p_dsEvent);
	this->CopyFrom(p_dsEvent);
	return *this;
}

MxDSAction* MxDSEvent::Clone() {
	MxDSEvent* clone = new MxDSEvent();

	if (clone) {
		*clone = *this;
	}

	return clone;
}
