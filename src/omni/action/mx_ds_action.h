#pragma once

#include "mx_ds_object.h"
#include "mx_geometry_3d.h"

class MxOmni;

class MxDSAction : public MxDSObject {
public:
	enum {
		c_looping = 0x01,
		c_bit3 = 0x04,
		c_bit4 = 0x08,
		c_bit5 = 0x10,
		c_enabled = 0x20,
		c_bit7 = 0x40,
		c_world = 0x80,
		c_bit9 = 0x100,
		c_bit10 = 0x200,
		c_bit11 = 0x400,
	};

	MxDSAction();
	~MxDSAction() override;

	MxDSAction(MxDSAction& p_dsAction);
	void CopyFrom(MxDSAction& p_dsAction);
	MxDSAction& operator=(MxDSAction& p_dsAction);

	static const char* ClassName() { return "MxDSAction"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSAction::ClassName()) ||
			   MxDSObject::IsA(p_name);
	}

	undefined4 VTable0x14() override;
	MxU32 GetSizeOnDisk() override;
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override;
	virtual MxLong GetDuration();
	virtual void SetDuration(MxLong p_duration);
	virtual MxDSAction* Clone();
	virtual void MergeFrom(MxDSAction& p_dsAction);
	virtual MxBool HasId(MxU32 p_objectId);
	virtual void SetUnknown90(MxLong p_unk0x90);
	virtual MxLong GetUnknown90();
	virtual MxLong GetElapsedTime();

	void AppendExtra(MxU16 p_extraLength, const char* p_extraData);

	void GetExtra(MxU16& p_extraLength, char*& p_extraData) {
		p_extraLength = m_extraLength;
		p_extraData = m_extraData;
	}

	MxU32 GetFlags() { return m_flags; }

	void SetFlags(MxU32 p_flags) { m_flags = p_flags; }

	char* GetExtraData() { return m_extraData; }
	MxU16 GetExtraLength() const { return m_extraLength; }

	MxLong GetStartTime() const { return m_startTime; }

	MxS32 GetLoopCount() { return m_loopCount; }

	void SetLoopCount(MxS32 p_loopCount) { m_loopCount = p_loopCount; }

	const Vector3& GetLocation() { return m_location; }

	const Vector3& GetDirection() { return m_direction; }

	const Vector3& GetUp() { return m_up; }

	void SetLocation(const Vector3& p_location) { m_location = p_location; }

	void SetDirection(const Vector3& p_direction) { m_direction = p_direction; }

	void SetUp(const Vector3& p_up) { m_up = p_up; }

	MxCore* GetUnknown84() { return m_unk0x84; }
	void SetUnknown84(MxCore* p_unk0x84) { m_unk0x84 = p_unk0x84; }
	MxCore* GetOrigin() { return m_origin; }
	void SetOrigin(MxCore* p_origin) { m_origin = p_origin; }

	MxBool IsLooping() const { return m_flags & c_looping; }
	MxBool IsBit3() const { return m_flags & c_bit3; }

	// MxDSAction::`scalar deleting destructor'

protected:
	MxU32 m_sizeOnDisk;
	MxU32 m_flags;
	MxLong m_startTime;
	MxLong m_duration;
	MxS32 m_loopCount;
	Mx3DPointFloat m_location;
	Mx3DPointFloat m_direction;
	Mx3DPointFloat m_up;
	char* m_extraData;
	MxU16 m_extraLength;
	MxCore* m_unk0x84;
	undefined4 m_unk0x88;
	MxCore* m_origin;
	MxLong m_unk0x90;
};

