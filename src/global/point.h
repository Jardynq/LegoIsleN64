#ifndef POINT_H
#define POINT_H

#include "types.h"

class Point {
public:
    Point();
    Point(i32 p_x, i32 p_y);
    Point(const Point& p_point);

    i32 GetX() const;
    i32 GetY() const;

    void SetX(i32 p_x);
    void SetY(i32 p_y);

private:
    i32 m_x;
    i32 m_y;
};

#endif // POINT_H
