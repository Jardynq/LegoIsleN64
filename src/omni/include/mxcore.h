#ifndef MXCORE_H
#define MXCORE_H

#include <string.h>

class MxParam;

class MxCore {
public:
	MxCore();
	virtual ~MxCore();
	virtual MxLong Notify(MxParam& p_param);

	virtual MxResult Tickle() { return SUCCESS; }

	virtual const char* ClassName() const { return "MxCore"; }

	virtual MxBool IsA(const char* p_name) const {
		return !strcmp(p_name, MxCore::ClassName());
	}

	MxU32 GetId() { return m_id; }

	// MxCore::`scalar deleting destructor'

private:
	static MxU32 g_nextCoreId;

	MxU32 m_id;
};

// MxCore::operator=

#endif // MXCORE_H
