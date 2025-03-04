#include "size.h"

Size::Size() {
}
Size::Size(i32 p_width, i32 p_height) {
	this->m_width = p_width;
	this->m_height = p_height;
}

i32 Size::GetWidth() const {
	return m_width;
}
i32 Size::GetHeight() const {
	return m_height;
}