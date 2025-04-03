#ifndef MXCOLLECTION_H
#define MXCOLLECTION_H

#include "mx_core.h"

template <class T>
class MxCollection : public MxCore {
public:
	MxCollection() : m_count(0) { SetDestroy(Destroy); }

	virtual MxS8 Compare(T, T) { return 0; }

	~MxCollection() override {}

	static void Destroy(T) {}

	void SetDestroy(void (*p_customDestructor)(T)) {
		this->m_customDestructor = p_customDestructor;
	}

protected:
	MxU32 m_count;
	void (*m_customDestructor)(T);
};

#endif // MXCOLLECTION_H
