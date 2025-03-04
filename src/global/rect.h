#ifndef RECT_H
#define RECT_H

#include "math.h"
#include "point.h"
#include "size.h"
#include "types.h"

class Rect {
public:
	Rect();
	Rect(i32 p_left, i32 p_top, i32 p_right, i32 p_bottom);
	Rect(const Point& p_point, const Size& p_size);
	Rect(const Rect& p_a, const Rect& p_b);

	Rect(const Rect& p_rect);

	void Intersect(const Rect& p_rect);

	void SetPoint(const Point& p_point);
	void AddPoint(const Point& p_point);

	void SubtractPoint(const Point& p_point);

	void UpdateBounds(const Rect& p_rect);

	bool IsValid() const;

	bool IntersectsWith(const Rect& p_rect) const;

	i32 GetWidth() const;
	i32 GetHeight() const;

	Point GetPoint() const;
	Size GetSize() const;

	i32 GetLeft() const;
	i32 GetTop() const;
	i32 GetRight() const;
	i32 GetBottom() const;

	void SetLeft(i32 p_left);
	void SetTop(i32 p_top);
	void SetRight(i32 p_right);
	void SetBottom(i32 p_bottom);

private:
	i32 m_left;
	i32 m_top;
	i32 m_right;
	i32 m_bottom;
};

#endif // RECT_H
