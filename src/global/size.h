#ifndef SIZE_H
#define SIZE_H

#include "types.h"

class Size {
public:
	Size();
	Size(i32 p_width, i32 p_height);

	i32 GetWidth() const;
	i32 GetHeight() const;

private:
	i32 m_width;
	i32 m_height;
};

#endif // SIZE_H
