#ifndef MXGEOMETRY3D_H
#define MXGEOMETRY3D_H

#include "realtime/vector3d.inl.h"

class Mx3DPointFloat : public Vector3 {
public:
	Mx3DPointFloat() : Vector3(m_elements) {}

	Mx3DPointFloat(float p_x, float p_y, float p_z) : Vector3(m_elements) {
		m_elements[0] = p_x;
		m_elements[1] = p_y;
		m_elements[2] = p_z;
	}

	Mx3DPointFloat(const Mx3DPointFloat& p_other) : Vector3(m_elements) {
		EqualsImpl(p_other.m_data);
	}

	Mx3DPointFloat(const Vector3& p_other) : Vector3(m_elements) {
		EqualsImpl(p_other.m_data);
	}

	virtual void operator=(const Vector3& p_impl) { EqualsImpl(p_impl.m_data); }

	float& operator[](int idx) { return m_data[idx]; }

	const float& operator[](int idx) const { return m_data[idx]; }

	// ??4Mx3DPointFloat@@QAEAAV0@ABV0@@Z

private:
	float m_elements[3];
};

#endif // MXGEOMETRY3D_H
