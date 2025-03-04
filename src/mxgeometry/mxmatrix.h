#ifndef MXMATRIX_H
#define MXMATRIX_H

#include "realtime/matrix4d.inl.h"

class MxMatrix : public Matrix4 {
public:
	MxMatrix() : Matrix4(m_elements) {}

	MxMatrix(const MxMatrix& p_matrix) : Matrix4(m_elements) {
		Equals(p_matrix);
	}

	MxMatrix(const Matrix4& p_matrix) : Matrix4(m_elements) {
		Equals(p_matrix);
	}

	float* operator[](int idx) { return m_data[idx]; }

	const float* operator[](int idx) const { return m_data[idx]; }

	void operator=(const Matrix4& p_matrix) override { Equals(p_matrix); }

	virtual void operator=(const MxMatrix& p_matrix) { Equals(p_matrix); }

private:
	float m_elements[4][4];
};

// Must be included here (not before MxMatrix) for correct ordering in binary.
// FromQuaternion and ToQuaternion in Matrix4 depend on Vector4.
// There's a chance they included mxgeometry4d.h after including this somewhere.
#include "realtime/vector4d.inl.h"

#endif // MXMATRIX_H
