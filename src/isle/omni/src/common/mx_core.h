#pragma once

#include <string.h>

class MxParam;

class MxCore {
public:
	MxCore();
	virtual ~MxCore();
	virtual MxLong Notify(MxParam& p_param);

	virtual MxResult Tickle() { return SUCCESS; }

	static const char* ClassName() { return "MxCore"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxCore::ClassName());
	}

	MxU32 GetId() { return m_id; }

private:
	static MxU32 g_nextCoreId;

	MxU32 m_id;
};

