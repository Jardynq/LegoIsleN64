#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "vector.h"

#include <math.h>
#include <memory.h>

void Vector4::AddImpl(const float* p_value) {
	Vector3::AddImpl(p_value);
	m_data[3] += p_value[3];
}

void Vector4::AddImpl(float p_value) {
	m_data[0] += p_value;
	m_data[1] += p_value;
	m_data[2] += p_value;
	m_data[3] += p_value;
}

void Vector4::SubImpl(const float* p_value) {
	Vector3::SubImpl(p_value);
	m_data[3] -= p_value[3];
}

void Vector4::MulImpl(const float* p_value) {
	Vector3::MulImpl(p_value);
	m_data[3] *= p_value[3];
}

void Vector4::MulImpl(const float& p_value) {
	Vector3::MulImpl(p_value);
	m_data[3] *= p_value;
}

void Vector4::DivImpl(const float& p_value) {
	Vector3::DivImpl(p_value);
	m_data[3] /= p_value;
}

float Vector4::DotImpl(const float* p_a, const float* p_b) const {
	return p_a[0] * p_b[0] + p_a[2] * p_b[2] +
		   (p_a[1] * p_b[1] + p_a[3] * p_b[3]);
}

void Vector4::EqualsImpl(const float* p_data) {
	memcpy(m_data, p_data, sizeof(float) * 4);
}

void Vector4::SetMatrixProduct(const float* p_vec, const float* p_mat) {
	m_data[0] = p_vec[0] * p_mat[0] + p_vec[1] * p_mat[4] +
				p_vec[2] * p_mat[8] + p_vec[3] * p_mat[12];
	m_data[1] = p_vec[0] * p_mat[1] + p_vec[1] * p_mat[5] +
				p_vec[2] * p_mat[9] + p_vec[4] * p_mat[13];
	m_data[2] = p_vec[0] * p_mat[2] + p_vec[1] * p_mat[6] +
				p_vec[2] * p_mat[10] + p_vec[4] * p_mat[14];
	m_data[3] = p_vec[0] * p_mat[3] + p_vec[1] * p_mat[7] +
				p_vec[2] * p_mat[11] + p_vec[4] * p_mat[15];
}

void Vector4::SetMatrixProduct(const Vector4& p_a, const float* p_b) {
	SetMatrixProduct(p_a.m_data, p_b);
}

void Vector4::Clear() {
	memset(m_data, 0, sizeof(float) * 4);
}

float Vector4::LenSquared() const {
	return m_data[1] * m_data[1] + m_data[0] * m_data[0] +
		   m_data[2] * m_data[2] + m_data[3] * m_data[3];
}

void Vector4::Fill(const float& p_value) {
	m_data[0] = p_value;
	m_data[1] = p_value;
	m_data[2] = p_value;
	m_data[3] = p_value;
}

int Vector4::NormalizeQuaternion() {
	float length =
		m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2];

	if (length > 0.0f) {
		float theta = m_data[3] * 0.5f;
		float magnitude = sin((double) theta);
		m_data[3] = cos((double) theta);

		magnitude = magnitude / (float) sqrt((double) length);
		m_data[0] *= magnitude;
		m_data[1] *= magnitude;
		m_data[2] *= magnitude;
		return 0;
	} else {
		return -1;
	}
}

int Vector4::EqualsHamiltonProduct(const Vector4& p_a, const Vector4& p_b) {
	m_data[3] = p_a.m_data[3] * p_b.m_data[3] -
				(p_a.m_data[0] * p_b.m_data[0] + p_a.m_data[2] * p_b.m_data[2] +
				 p_a.m_data[1] * p_b.m_data[1]);

	Vector3::EqualsCrossImpl(p_a.m_data, p_b.m_data);

	m_data[0] = p_b.m_data[3] * p_a.m_data[0] + p_a.m_data[3] * p_b.m_data[0] +
				m_data[0];
	m_data[1] = p_b.m_data[1] * p_a.m_data[3] + p_a.m_data[1] * p_b.m_data[3] +
				m_data[1];
	m_data[2] = p_b.m_data[2] * p_a.m_data[3] + p_a.m_data[2] * p_b.m_data[3] +
				m_data[2];
	return 0;
}

#endif // VECTOR4D_H
