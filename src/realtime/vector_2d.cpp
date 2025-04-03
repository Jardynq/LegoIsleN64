#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "vector.h"

#include <math.h>
#include <memory.h>

void Vector2::AddImpl(const float* p_value) {
	m_data[0] += p_value[0];
	m_data[1] += p_value[1];
}

void Vector2::AddImpl(float p_value) {
	m_data[0] += p_value;
	m_data[1] += p_value;
}

void Vector2::SubImpl(const float* p_value) {
	m_data[0] -= p_value[0];
	m_data[1] -= p_value[1];
}

void Vector2::MulImpl(const float* p_value) {
	m_data[0] *= p_value[0];
	m_data[1] *= p_value[1];
}

void Vector2::MulImpl(const float& p_value) {
	m_data[0] *= p_value;
	m_data[1] *= p_value;
}

void Vector2::DivImpl(const float& p_value) {
	m_data[0] /= p_value;
	m_data[1] /= p_value;
}

float Vector2::DotImpl(const float* p_a, const float* p_b) const {
	return p_b[0] * p_a[0] + p_b[1] * p_a[1];
}

void Vector2::SetData(float* p_data) {
	m_data = p_data;
}

void Vector2::EqualsImpl(const float* p_data) {
	memcpy(m_data, p_data, sizeof(float) * 2);
}

float* Vector2::GetData() {
	return m_data;
}

const float* Vector2::GetData() const {
	return m_data;
}

void Vector2::Clear() {
	memset(m_data, 0, sizeof(float) * 2);
}

float Vector2::Dot(const float* p_a, const float* p_b) const {
	return DotImpl(p_a, p_b);
}

float Vector2::Dot(const Vector2& p_a, const Vector2& p_b) const {
	return DotImpl(p_a.m_data, p_b.m_data);
}

float Vector2::Dot(const float* p_a, const Vector2& p_b) const {
	return DotImpl(p_a, p_b.m_data);
}

float Vector2::Dot(const Vector2& p_a, const float* p_b) const {
	return DotImpl(p_a.m_data, p_b);
}

float Vector2::LenSquared() const {
	return m_data[0] * m_data[0] + m_data[1] * m_data[1];
}

int Vector2::Unitize() {
	float sq = LenSquared();

	if (sq > 0.0f) {
		sq = sqrt(sq);
		if (sq > 0.0f) {
			DivImpl(sq);
			return 0;
		}
	}

	return -1;
}

void Vector2::operator+=(float p_value) {
	AddImpl(p_value);
}

void Vector2::operator+=(const float* p_other) {
	AddImpl(p_other);
}

void Vector2::operator+=(const Vector2& p_other) {
	AddImpl(p_other.m_data);
}

void Vector2::operator-=(const float* p_other) {
	SubImpl(p_other);
}

void Vector2::operator-=(const Vector2& p_other) {
	SubImpl(p_other.m_data);
}

void Vector2::operator*=(const float* p_other) {
	MulImpl(p_other);
}

void Vector2::operator*=(const Vector2& p_other) {
	MulImpl(p_other.m_data);
}

void Vector2::operator*=(const float& p_value) {
	MulImpl(p_value);
}

void Vector2::operator/=(const float& p_value) {
	DivImpl(p_value);
}

void Vector2::operator=(const float* p_other) {
	EqualsImpl(p_other);
}

void Vector2::operator=(const Vector2& p_other) {
	EqualsImpl(p_other.m_data);
}

#endif // VECTOR2D_H
