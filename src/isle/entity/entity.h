#pragma once

#include "extra.h"
#include "mx_entity.h"

class LegoROI;
class MxDSAction;
class Vector3;

class LegoEntity : public MxEntity {
public:
	enum Type { e_actor = 0, e_unk1, e_plant, e_building, e_autoROI };

	enum { c_bit1 = 0x01, c_managerOwned = 0x02 };

	enum { c_altBit1 = 0x01 };

	LegoEntity() { Init(); }

	~LegoEntity() override { Destroy(TRUE); }

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "LegoEntity"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoEntity::ClassName()) ||
			   MxEntity::IsA(p_name);
	}

	virtual MxResult Create(MxDSAction& p_dsAction);
	virtual void Destroy(MxBool p_fromDestructor);
	virtual void ParseAction(char* p_extra);
	virtual void SetROI(LegoROI* p_roi, MxBool p_bool1, MxBool p_bool2);
	virtual void SetWorldTransform(
		const Vector3& p_location,
		const Vector3& p_direction,
		const Vector3& p_up
	);
	virtual void ResetWorldTransform(MxBool p_cameraFlag);

	virtual void SetWorldSpeed(MxFloat p_worldSpeed) {
		m_worldSpeed = p_worldSpeed;
	}

	virtual void ClickSound(MxBool p_und);
	virtual void ClickAnimation();
	virtual void SwitchVariant();
	virtual void SwitchSound();
	virtual void SwitchMove();
	virtual void SwitchColor(LegoROI* p_roi);
	virtual void SwitchMood();

	void FUN_10010c30();
	void SetType(MxU8 p_type);
	void SetLocation(
		const Vector3& p_location,
		const Vector3& p_direction,
		const Vector3& p_up,
		MxBool p_und
	);
	Mx3DPointFloat GetWorldDirection();
	Mx3DPointFloat GetWorldUp();
	Mx3DPointFloat GetWorldPosition();

	MxBool GetUnknown0x10IsSet(MxU8 p_flag) { return m_unk0x10 & p_flag; }
	MxBool GetFlagsIsSet(MxU8 p_flag) { return m_flags & p_flag; }
	MxU8 GetFlags() { return m_flags; }

	MxFloat GetWorldSpeed() { return m_worldSpeed; }

	LegoROI* GetROI() { return m_roi; }

	MxU8 GetType() { return m_type; }

	MxBool GetCameraFlag() { return m_cameraFlag; }

	void SetFlags(MxU8 p_flags) { m_flags = p_flags; }
	void SetFlag(MxU8 p_flag) { m_flags |= p_flag; }
	void ClearFlag(MxU8 p_flag) { m_flags &= ~p_flag; }
	void SetUnknown0x10Flag(MxU8 p_flag) { m_unk0x10 |= p_flag; }
	void ClearUnknown0x10Flag(MxU8 p_flag) { m_unk0x10 &= ~p_flag; }

protected:
	void Init();
	void SetWorld();

	MxU8 m_unk0x10;
	MxU8 m_flags;
	Mx3DPointFloat m_worldLocation;
	Mx3DPointFloat m_worldDirection;
	Mx3DPointFloat m_worldUp;
	MxFloat m_worldSpeed;
	LegoROI* m_roi;
	MxBool m_cameraFlag;
	MxU8 m_type; // For tokens from the extra string that look like this:
	// "Action:openram;\lego\scripts\Race\CarRaceR;0"
	Extra::ActionType m_actionType;
	// variable name verified by BETA10 0x1007eddf
	char* m_siFile;
	MxS32 m_targetEntityId;
};

// LegoEntity::`scalar deleting destructor'

