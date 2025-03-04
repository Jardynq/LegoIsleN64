#include "point.h"

Point::Point() {
}
Point::Point(i32 p_x, i32 p_y) {
	this->m_x = p_x;
	this->m_y = p_y;
}
Point::Point(const Point& p_point) {
	this->m_x = p_point.m_x;
	this->m_y = p_point.m_y;
}

i32 Point::GetX() const {
	return m_x;
}
i32 Point::GetY() const {
	return m_y;
}

void Point::SetX(i32 p_x) {
	m_x = p_x;
}
void Point::SetY(i32 p_y) {
	m_y = p_y;
}
