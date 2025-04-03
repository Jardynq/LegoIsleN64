#ifndef __LEGOSPHERE_H
#define __LEGOSPHERE_H

#include "vertex.h"

class LegoSphere {
public:
	LegoSphere() { m_radius = 0.0F; }
	LegoVertex& GetCenter() { return m_center; }
	void SetCenter(LegoVertex& p_center) { m_center = p_center; }
	LegoFloat GetRadius() { return m_radius; }
	void SetRadius(LegoFloat p_radius) { m_radius = p_radius; }
	LegoResult Read(LegoStorage* p_storage);

protected:
	LegoVertex m_center;
	LegoFloat m_radius;
};

#endif // __LEGOSPHERE_H
