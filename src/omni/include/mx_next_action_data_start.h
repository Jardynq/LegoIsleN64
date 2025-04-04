#pragma once

#include "mx_core.h"

class MxNextActionDataStart : public MxCore {
public:
	// inlined constructor at 0x100c1847
	MxNextActionDataStart(MxU32 p_objectId, MxS16 p_unk0x24, MxU32 p_data)
		: m_objectId(p_objectId), m_unk0x24(p_unk0x24), m_data(p_data) {}

	static const char* ClassName() { return "MxNextActionDataStart"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxNextActionDataStart::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	MxU32 GetObjectId() const { return m_objectId; }
	MxS16 GetUnknown24() const { return m_unk0x24; }
	MxU32 GetData() const { return m_data; }
	void SetData(MxU32 p_data) { m_data = p_data; }

	// MxNextActionDataStart::`scalar deleting destructor'

private:
	MxU32 m_objectId;
	MxS16 m_unk0x24;
	MxU32 m_data;
};

