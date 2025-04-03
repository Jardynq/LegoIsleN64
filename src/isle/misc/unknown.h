#ifndef __LEGOUNKNOWN_H
#define __LEGOUNKNOWN_H

#include "mx_geometry_3d.h"

class MxMatrix;

class LegoUnknown {
public:
	LegoUnknown();
	~LegoUnknown();

	void FUN_1009a140(
		const Vector3& p_point1,
		const Vector3& p_point2,
		const Vector3& p_point3,
		const Vector3& p_point4
	);
	LegoResult
	FUN_1009a1e0(float p_f1, MxMatrix& p_mat, Vector3& p_v, LegoU32 p_und);

private:
	Mx3DPointFloat m_unk0x00[4];
};

#endif // __LEGOUNKNOWN_H
