#include "mxdsaction.h"

#include "mxmisc.h"
#include "mxtimer.h"
#include "mxutilities.h"

#include <assert.h>
#include <float.h>
#include <limits.h>

MxU16 g_sep = TWOCC(',', ' ');

MxDSAction::MxDSAction() {
	m_type = e_action;
	m_flags = MxDSAction::c_enabled;
	m_extraLength = 0;
	m_extraData = NULL;
	m_startTime = INT_MIN;
	m_duration = INT_MIN;
	m_loopCount = -1;
	m_location.Fill(FLT_MAX);
	m_direction.Fill(FLT_MAX);
	m_up.Fill(FLT_MAX);
	m_unk0x84 = NULL;
	m_unk0x88 = 0;
	m_origin = NULL;
	m_unk0x90 = INT_MIN;
}

MxLong MxDSAction::GetDuration() {
	return m_duration;
}

void MxDSAction::SetDuration(MxLong p_duration) {
	m_duration = p_duration;
}

MxBool MxDSAction::HasId(MxU32 p_objectId) {
	return m_objectId == p_objectId;
}

void MxDSAction::SetUnknown90(MxLong p_unk0x90) {
	m_unk0x90 = p_unk0x90;
}

MxLong MxDSAction::GetUnknown90() {
	return m_unk0x90;
}

MxDSAction::~MxDSAction() {
	delete[] m_extraData;
}

void MxDSAction::CopyFrom(MxDSAction& p_dsAction) {
	m_objectId = p_dsAction.m_objectId;
	m_flags = p_dsAction.m_flags;
	m_startTime = p_dsAction.m_startTime;
	m_duration = p_dsAction.m_duration;
	m_loopCount = p_dsAction.m_loopCount;
	m_location = p_dsAction.m_location;
	m_direction = p_dsAction.m_direction;
	m_up = p_dsAction.m_up;
	AppendExtra(p_dsAction.m_extraLength, p_dsAction.m_extraData);
	m_unk0x84 = p_dsAction.m_unk0x84;
	m_unk0x88 = p_dsAction.m_unk0x88;
	m_origin = p_dsAction.m_origin;
	m_unk0x90 = p_dsAction.m_unk0x90;
}

MxDSAction::MxDSAction(MxDSAction& p_dsAction) : MxDSObject(p_dsAction) {
	CopyFrom(p_dsAction);
}

undefined4 MxDSAction::VTable0x14() {
	return MxDSObject::VTable0x14();
}

MxU32 MxDSAction::GetSizeOnDisk() {
	MxU32 size = MxDSObject::GetSizeOnDisk();
	size += sizeof(m_flags);
	size += sizeof(m_startTime);
	size += sizeof(m_duration);
	size += sizeof(m_loopCount);
	size += sizeof(double) * 3; // m_location
	size += sizeof(double) * 3; // m_direction
	size += sizeof(double) * 3; // m_up
	size += sizeof(m_extraLength);
	size += m_extraLength;

	m_sizeOnDisk = size - MxDSObject::GetSizeOnDisk();

	return size;
}

MxDSAction& MxDSAction::operator=(MxDSAction& p_dsAction) {
	if (this == &p_dsAction) {
		return *this;
	}

	MxDSObject::operator=(p_dsAction);
	CopyFrom(p_dsAction);
	return *this;
}

MxDSAction* MxDSAction::Clone() {
	MxDSAction* clone = new MxDSAction();

	if (clone) {
		*clone = *this;
	}

	return clone;
}

MxLong MxDSAction::GetElapsedTime() {
	return Timer()->GetTime() - m_unk0x90;
}

void MxDSAction::MergeFrom(MxDSAction& p_dsAction) {
	if (p_dsAction.GetStartTime() != INT_MIN) {
		m_startTime = p_dsAction.GetStartTime();
	}

	if (p_dsAction.GetDuration() != INT_MIN) {
		m_duration = p_dsAction.GetDuration();
	}

	if (p_dsAction.GetLoopCount() != -1) {
		m_loopCount = p_dsAction.GetLoopCount();
	}

	if (p_dsAction.GetLocation()[0] != FLT_MAX) {
		m_location[0] = p_dsAction.GetLocation()[0];
	}
	if (p_dsAction.GetLocation()[1] != FLT_MAX) {
		m_location[1] = p_dsAction.GetLocation()[1];
	}
	if (p_dsAction.GetLocation()[2] != FLT_MAX) {
		m_location[2] = p_dsAction.GetLocation()[2];
	}

	if (p_dsAction.GetDirection()[0] != FLT_MAX) {
		m_direction[0] = p_dsAction.GetDirection()[0];
	}
	if (p_dsAction.GetDirection()[1] != FLT_MAX) {
		m_direction[1] = p_dsAction.GetDirection()[1];
	}
	if (p_dsAction.GetDirection()[2] != FLT_MAX) {
		m_direction[2] = p_dsAction.GetUp()[2]; // This is correct
	}

	if (p_dsAction.GetUp()[0] != FLT_MAX) {
		m_up[0] = p_dsAction.GetUp()[0];
	}
	if (p_dsAction.GetUp()[1] != FLT_MAX) {
		m_up[1] = p_dsAction.GetUp()[1];
	}
	if (p_dsAction.GetUp()[2] != FLT_MAX) {
		m_up[2] = p_dsAction.GetUp()[2];
	}

	MxU16 extraLength;
	char* extraData;
	p_dsAction.GetExtra(extraLength, extraData);

	if (extraLength && extraData) {
		if (!m_extraData || !strncmp("XXX", m_extraData, 3)) {
			delete[] m_extraData;
			m_extraLength = 0;
			AppendExtra(extraLength, extraData);
		}
	}
}

void MxDSAction::AppendExtra(MxU16 p_extraLength, const char* p_extraData) {
	if (m_extraData == p_extraData) {
		return;
	}

	if (p_extraData) {
		if (m_extraLength) {
			char* newExtra =
				new char[p_extraLength + m_extraLength + sizeof(g_sep)];
			assert(newExtra);
			memcpy(newExtra, m_extraData, m_extraLength);
			memcpy(&newExtra[m_extraLength], &g_sep, sizeof(g_sep));
			memcpy(
				&newExtra[m_extraLength + sizeof(g_sep)],
				p_extraData,
				p_extraLength
			);

			m_extraLength += p_extraLength + sizeof(g_sep);
			delete[] m_extraData;
			m_extraData = newExtra;
		} else {
			m_extraData = new char[p_extraLength];

			if (m_extraData) {
				m_extraLength = p_extraLength;
				memcpy(m_extraData, p_extraData, p_extraLength);
			} else {
				assert(0);
			}
		}
	}
}

void MxDSAction::Deserialize(MxU8*& p_source, MxS16 p_unk0x24) {
	MxDSObject::Deserialize(p_source, p_unk0x24);

	// clang-format off
	m_flags = *(MxU32*)p_source;  p_source += sizeof(m_flags);
	m_startTime = *(MxLong*)p_source;  p_source += sizeof(m_startTime);
	m_duration = *(MxLong*)p_source;  p_source += sizeof(m_duration);
	m_loopCount = *(MxS32*)p_source;  p_source += sizeof(m_loopCount);
	m_location[0] = *(double*)p_source;  p_source += sizeof(double);
	m_location[1] = *(double*)p_source;  p_source += sizeof(double);
	m_location[2] = *(double*)p_source;  p_source += sizeof(double);
	m_direction[0] = *(double*)p_source;  p_source += sizeof(double);
	m_direction[1] = *(double*)p_source;  p_source += sizeof(double);
	m_direction[2] = *(double*)p_source;  p_source += sizeof(double);
	m_up[0] = *(double*)p_source;  p_source += sizeof(double);
	m_up[1] = *(double*)p_source;  p_source += sizeof(double);
	m_up[2] = *(double*)p_source;  p_source += sizeof(double);

	MxU16 extraLength = *(MxU16*)p_source;  p_source += sizeof(extraLength);
	// clang-format on

	if (extraLength) {
		AppendExtra(extraLength, (char*) p_source);
		p_source += extraLength;
	}
}
