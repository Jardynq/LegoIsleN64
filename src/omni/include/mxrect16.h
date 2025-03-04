#ifndef MXRECT16_H
#define MXRECT16_H

struct MxRect16 {

	MxRect16() {}

	void SetLeft(MxS16 p_left) { m_left = p_left; }

	void SetTop(MxS16 p_top) { m_top = p_top; }

	void SetRight(MxS16 p_right) { m_right = p_right; }

	void SetBottom(MxS16 p_bottom) { m_bottom = p_bottom; }

	MxS16 GetLeft() const { return m_left; }

	MxS16 GetTop() const { return m_top; }

	// There is no GetRight()

	MxS16 GetBottom() const { return m_bottom; }

	MxS16 GetWidth() const { return m_right - m_left + 1; }

	MxS16 GetHeight() const { return m_bottom - m_top + 1; }

private:
	MxS16 m_left;
	MxS16 m_top;
	MxS16 m_right;
	MxS16 m_bottom;
};

#endif // MXRECT16_H
