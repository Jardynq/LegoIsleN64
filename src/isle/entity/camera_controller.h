#pragma once

#include "point_of_view_controller.h"
#include "mx_geometry_3d.h"
#include "mx_matrix.h"
#include "mx_point32.h"


class LegoCameraController : public LegoPointOfViewController {
public:
	LegoCameraController();
	~LegoCameraController() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "LegoCameraController"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ClassName()) || MxCore::IsA(p_name);
	}

	virtual void OnLButtonDown(MxPoint32 p_point);
	virtual void OnLButtonUp(MxPoint32 p_point);
	virtual void OnRButtonDown(MxPoint32 p_point);
	virtual void OnRButtonUp(MxPoint32 p_point);
	virtual void OnMouseMove(MxU8 p_modifier, MxPoint32 p_point);
	virtual MxResult Create();

	void SetWorldTransform(
		const Vector3& p_at,
		const Vector3& p_dir,
		const Vector3& p_up
	);
	void FUN_10012290(float p_angle);
	void FUN_10012320(float p_angle);
	MxResult FUN_100123b0(Matrix4& p_matrix);
	void FUN_100123e0(const Matrix4& p_transform, MxU32 p_und);
	Mx3DPointFloat GetWorldUp();
	Mx3DPointFloat GetWorldLocation();
	Mx3DPointFloat GetWorldDirection();

private:
	MxMatrix m_matrix1;
	MxMatrix m_matrix2;
};

// LegoCameraController::`scalar deleting destructor'

