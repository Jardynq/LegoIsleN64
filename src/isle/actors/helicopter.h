#pragma once

#include "isle_path_actor.h"
#include "state.h"
#include "mx_quaternion.h"

class Act3;

class HelicopterState : public LegoState {
public:
	HelicopterState() : m_unk0x08(0) {}

	MxBool IsSerializable() override { return FALSE; }

	MxBool Reset() override {
		m_unk0x08 = 0;
		return TRUE;
	}

	static const char* ClassName() { return "HelicopterState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, HelicopterState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	// HelicopterState::`scalar deleting destructor'

	MxU32 m_unk0x08;
};

class Helicopter : public IslePathActor {
public:
	Helicopter();
	~Helicopter() override;

	static const char* ClassName() { return "Helicopter"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Helicopter::ClassName()) ||
			   IslePathActor::IsA(p_name);
	}

	MxResult Create(MxDSAction& p_dsAction) override;
	void Animate(float p_time) override;
	void VTable0x74(Matrix4& p_transform) override;
	MxLong HandleClick() override;
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;
	MxLong HandleEndAnim(LegoEndAnimNotificationParam& p_param) override;
	void Exit() override;

	void CreateState();
	void FUN_10004640(const Matrix4& p_matrix);
	void FUN_10004670(const Matrix4& p_matrix);

	// Helicopter::`scalar deleting destructor'

	// m_state is accessed directly from Act3; confirmed by BETA10
	friend class Act3;

protected:
	void FUN_100042a0(const Matrix4& p_matrix);

	MxMatrix m_unk0x160;
	MxMatrix m_unk0x1a8;
	float m_unk0x1f0;
	MxQuaternionTransformer m_unk0x1f4;
	HelicopterState* m_state;
	MxAtomId m_script;
};

