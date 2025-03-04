#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

// Note: virtual function overloads appear in the virtual table
// in reverse order of appearance.

struct UnknownMatrixType {
	float m_data[4][4];
};

class Matrix4 {
protected:
	float (*m_data)[4];

public:
	Matrix4(float (*p_data)[4]) { SetData(p_data); }

	inline virtual void Equals(float (*p_data)[4]);
	inline virtual void Equals(const Matrix4& p_matrix);
	inline virtual void SetData(float (*p_data)[4]);
	inline virtual void SetData(UnknownMatrixType& p_matrix);
	inline virtual float (*GetData())[4];
	inline virtual float (*GetData() const)[4];
	inline virtual float* Element(int p_row, int p_col);
	inline virtual const float* Element(int p_row, int p_col) const;
	inline virtual void Clear();
	inline virtual void SetIdentity();
	inline virtual void operator=(const Matrix4& p_matrix);
	inline virtual Matrix4& operator+=(float (*p_data)[4]);
	inline virtual void
	TranslateBy(const float& p_x, const float& p_y, const float& p_z);
	inline virtual void
	SetTranslation(const float& p_x, const float& p_y, const float& p_z);
	inline virtual void Product(float (*p_a)[4], float (*p_b)[4]);
	inline virtual void Product(const Matrix4& p_a, const Matrix4& p_b);
	inline virtual void ToQuaternion(Vector4& p_resultQuat);
	inline virtual int FromQuaternion(const Vector4& p_vec);

	inline void Scale(const float& p_x, const float& p_y, const float& p_z);
	inline void RotateX(const float& p_angle);
	inline void RotateY(const float& p_angle);
	inline void RotateZ(const float& p_angle);
	inline int BETA_1005a590(Matrix4& p_mat);
	inline void Swap(int p_d1, int p_d2);

	float* operator[](int idx) { return m_data[idx]; }

	const float* operator[](int idx) const { return m_data[idx]; }
};

#include "matrix4d.inl.h"

#endif // MATRIX_H
