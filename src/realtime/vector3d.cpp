#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "vector.h"

void Vector3::EqualsCrossImpl(const float* p_a, const float* p_b) {
	m_data[0] = p_a[1] * p_b[2] - p_a[2] * p_b[1];
	m_data[1] = p_a[2] * p_b[0] - p_a[0] * p_b[2];
	m_data[2] = p_a[0] * p_b[1] - p_a[1] * p_b[0];
}

void Vector3::EqualsCross(const Vector3& p_a, const Vector3& p_b) {
	EqualsCrossImpl(p_a.m_data, p_b.m_data);
}

void Vector3::EqualsCross(const Vector3& p_a, const float* p_b) {
	EqualsCrossImpl(p_a.m_data, p_b);
}

void Vector3::EqualsCross(const float* p_a, const Vector3& p_b) {
	EqualsCrossImpl(p_a, p_b.m_data);
}

void Vector3::AddImpl(const float* p_value) {
	Vector2::AddImpl(p_value);
	m_data[2] += p_value[2];
}

void Vector3::AddImpl(float p_value) {
	m_data[0] += p_value;
	m_data[1] += p_value;
	m_data[2] += p_value;
}

void Vector3::SubImpl(const float* p_value) {
	Vector2::SubImpl(p_value);
	m_data[2] -= p_value[2];
}

void Vector3::MulImpl(const float* p_value) {
	Vector2::MulImpl(p_value);
	m_data[2] *= p_value[2];
}

void Vector3::MulImpl(const float& p_value) {
	Vector2::MulImpl(p_value);
	m_data[2] *= p_value;
}

void Vector3::DivImpl(const float& p_value) {
	Vector2::DivImpl(p_value);
	m_data[2] /= p_value;
}

float Vector3::DotImpl(const float* p_a, const float* p_b) const {
	return p_a[0] * p_b[0] + p_a[1] * p_b[1] + p_a[2] * p_b[2];
}

void Vector3::EqualsImpl(const float* p_data) {
	memcpy(m_data, p_data, sizeof(float) * 3);
}

void Vector3::Clear() {
	memset(m_data, 0, sizeof(float) * 3);
}

float Vector3::LenSquared() const {
	return m_data[0] * m_data[0] + m_data[1] * m_data[1] +
		   m_data[2] * m_data[2];
}

void Vector3::Fill(const float& p_value) {
	m_data[0] = p_value;
	m_data[1] = p_value;
	m_data[2] = p_value;
}

#endif // VECTOR3D_H
