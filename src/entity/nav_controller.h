#ifndef __LEGONAVCONTROLLER_H
#define __LEGONAVCONTROLLER_H

#include "mx_core.h"

struct LegoLocation;
class Vector3;

//////////////////////////////////////////////////////////////////////////////
//
// LegoMouseController

class LegoNavController : public MxCore {
public:
	LegoNavController();
	~LegoNavController() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "LegoNavController"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ClassName()) || MxCore::IsA(p_name);
	}

	void SetTargets(int p_hPos, int p_vPos, MxBool p_accel);
	void SetControlMax(int p_hMax, int p_vMax);
	void SetToDefaultParams();
	MxBool CalculateNewPosDir(
		const Vector3& p_curPos,
		const Vector3& p_curDir,
		Vector3& p_newPos,
		Vector3& p_newDir,
		const Vector3* p_und
	);

	static void GetDefaults(
		int* p_dz,
		float* p_lv,
		float* p_rv,
		float* p_la,
		float* p_ra,
		float* p_ld,
		float* p_rd,
		float* p_lmina,
		float* p_rmina,
		float* p_rs,
		MxBool* p_urs
	);
	static void SetDefaults(
		int p_dz,
		float p_lv,
		float p_rv,
		float p_la,
		float p_ra,
		float p_ld,
		float p_rd,
		float p_lmina,
		float p_rmina,
		float p_rs,
		MxBool p_urs
	);
	static MxResult UpdateLocation(MxU32 p_location);
	static MxResult UpdateLocation(const char* p_location);
	static MxS32 GetNumLocations();
	static LegoLocation* GetLocation(MxU32 p_location);

	void SetLinearVel(MxFloat p_linearVel) { m_linearVel = p_linearVel; }

	void SetDeadZone(MxS32 p_deadZone) { m_deadZone = p_deadZone; }

	void SetTrackDefault(MxS32 p_trackDefault) {
		m_trackDefault = p_trackDefault;
	}

	void Reset() {
		m_trackDefault = TRUE;
		SetToDefaultParams();
	}

	MxFloat GetLinearVel() { return m_linearVel; }
	MxFloat GetRotationalVel() { return m_rotationalVel; }
	MxFloat GetMaxLinearVel() { return m_maxLinearVel; }
	MxFloat GetMaxLinearAccel() { return m_maxLinearAccel; }
	MxFloat GetMaxLinearDeccel() { return m_maxLinearDeccel; }
	void ResetMaxLinearVel(MxFloat p_maxLinearVel) {
		m_maxLinearVel = p_maxLinearVel;
		m_trackDefault = FALSE;
	}
	void ResetMaxLinearAccel(MxFloat p_maxLinearAccel) {
		m_maxLinearAccel = p_maxLinearAccel;
		m_trackDefault = FALSE;
	}
	void ResetMaxLinearDeccel(MxFloat p_maxLinearDeccel) {
		m_maxLinearDeccel = p_maxLinearDeccel;
		m_trackDefault = FALSE;
	}

	int GetDefaultDeadZone() { return g_defdeadZone; }

	// LegoNavController::`scalar deleting destructor'

protected:
	float CalculateNewVel(
		float p_targetVel,
		float p_currentVel,
		float p_accel,
		float p_time
	);
	float CalculateNewTargetVel(int p_pos, int p_center, float p_max);
	float CalculateNewAccel(int p_pos, int p_center, float p_max, int p_min);

	MxResult ProcessJoystickInput(MxBool& p_und);
	MxResult ProcessKeyboardInput();

	int m_hMax;
	int m_vMax;
	int m_deadZone;
	float m_zeroThreshold;
	float m_linearVel;
	float m_rotationalVel;
	float m_targetLinearVel;
	float m_targetRotationalVel;
	float m_maxLinearVel;
	float m_maxRotationalVel;
	float m_linearAccel;
	float m_rotationalAccel;
	float m_maxLinearAccel;
	float m_maxRotationalAccel;
	float m_minLinearAccel;
	float m_minRotationalAccel;
	float m_maxLinearDeccel;
	float m_maxRotationalDeccel;
	float m_rotSensitivity;
	MxBool m_useRotationalVel;
	MxTime m_lastTime;
	MxBool m_trackDefault;
	MxBool m_unk0x5d;
	float m_unk0x60;
	float m_unk0x64;
	float m_unk0x68;
	MxBool m_unk0x6c;
	// one copy of defaults (these can be set by App.)
	static int g_defdeadZone;
	static float g_defzeroThreshold;
	static float g_defmaxLinearVel;
	static float g_defmaxRotationalVel;
	static float g_defmaxLinearAccel;
	static float g_defmaxRotationalAccel;
	static float g_defminLinearAccel;
	static float g_defminRotationalAccel;
	static float g_defmaxLinearDeccel;
	static float g_defmaxRotationalDeccel;
	static float g_defrotSensitivity;
	static MxBool g_defuseRotationalVel;
};

#endif // __LEGOPOVCONTROLLER_H
