#include "rect.h"

Rect::Rect() {}
Rect::Rect(i32 p_left, i32 p_top, i32 p_right, i32 p_bottom) {
    this->m_left = p_left;
    this->m_top = p_top;
    this->m_right = p_right;
    this->m_bottom = p_bottom;
}
Rect::Rect(const Point& p_point, const Size& p_size) {
    this->m_left = p_point.GetX();
    this->m_top = p_point.GetY();
    this->m_right = p_size.GetWidth() + p_point.GetX() - 1;
    this->m_bottom = p_size.GetHeight() + p_point.GetY() - 1;
}
Rect::Rect(const Rect& p_a, const Rect& p_b) {
    m_left = Max(p_a.m_left, p_b.m_left);
    m_top = Max(p_a.m_top, p_b.m_top);
    m_right = Min(p_a.m_right, p_b.m_right);
    m_bottom = Min(p_a.m_bottom, p_b.m_bottom);
}

Rect::Rect(const Rect& p_rect) {
    this->m_left = p_rect.m_left;
    this->m_top = p_rect.m_top;
    this->m_right = p_rect.m_right;
    this->m_bottom = p_rect.m_bottom;
}

void Rect::Intersect(const Rect& p_rect) {
    m_left = Max(p_rect.m_left, m_left);
    m_top = Max(p_rect.m_top, m_top);
    m_right = Min(p_rect.m_right, m_right);
    m_bottom = Min(p_rect.m_bottom, m_bottom);
}

void Rect::SetPoint(const Point& p_point) {
    this->m_left = p_point.GetX();
    this->m_top = p_point.GetY();
}

void Rect::AddPoint(const Point& p_point) {
    this->m_left += p_point.GetX();
    this->m_top += p_point.GetY();
    this->m_right += p_point.GetX();
    this->m_bottom += p_point.GetY();
}

void Rect::SubtractPoint(const Point& p_point) {
    this->m_left -= p_point.GetX();
    this->m_top -= p_point.GetY();
    this->m_right -= p_point.GetX();
    this->m_bottom -= p_point.GetY();
}

void Rect::UpdateBounds(const Rect& p_rect) {
    m_left = Min(m_left, p_rect.m_left);
    m_top = Min(m_top, p_rect.m_top);
    m_right = Max(m_right, p_rect.m_right);
    m_bottom = Max(m_bottom, p_rect.m_bottom);
}

bool Rect::IsValid() const { return m_left < m_right && m_top < m_bottom; }

bool Rect::IntersectsWith(const Rect& p_rect) const {
    return m_left < p_rect.m_right && p_rect.m_left < m_right && m_top < p_rect.m_bottom && p_rect.m_top < m_bottom;
}

i32 Rect::GetWidth() const { return (m_right - m_left) + 1; }
i32 Rect::GetHeight() const { return (m_bottom - m_top) + 1; }

Point Rect::GetPoint() const { return Point(this->m_left, this->m_top); }
Size Rect::GetSize() const { return Size(this->m_right, this->m_bottom); }

i32 Rect::GetLeft() const { return m_left; }
i32 Rect::GetTop() const { return m_top; }
i32 Rect::GetRight() const { return m_right; }
i32 Rect::GetBottom() const { return m_bottom; }

void Rect::SetLeft(i32 p_left) { m_left = p_left; }
void Rect::SetTop(i32 p_top) { m_top = p_top; }
void Rect::SetRight(i32 p_right) { m_right = p_right; }
void Rect::SetBottom(i32 p_bottom) { m_bottom = p_bottom; }
