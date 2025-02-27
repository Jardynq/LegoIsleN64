#ifndef MXCORE_H
#define MXCORE_H

#include "mxtypes.h"

#include <string.h>

class MxParam;

// VTABLE: LEGO1 0x100dc0f8
// VTABLE: BETA10 0x101c1bc8
// SIZE 0x08
class MxCore {
public:
	MxCore();
	virtual ~MxCore();                       // vtable+00
	virtual MxLong Notify(MxParam& p_param); // vtable+04

	// FUNCTION: LEGO1 0x10001f70
	// FUNCTION: BETA10 0x1000f380
	virtual MxResult Tickle() { return SUCCESS; } // vtable+08

	// FUNCTION: LEGO1 0x100144c0
	// FUNCTION: BETA10 0x100126d0
	virtual const char* ClassName() const // vtable+0c
	{
		// STRING: LEGO1 0x100f007c
		return "MxCore";
	}

	// FUNCTION: LEGO1 0x100140d0
	// FUNCTION: BETA10 0x10012680
	virtual MxBool IsA(const char* p_name) const // vtable+10
	{
		return !strcmp(p_name, MxCore::ClassName());
	}

	MxU32 GetId() { return m_id; }

	// SYNTHETIC: LEGO1 0x100ae1c0
	// SYNTHETIC: BETA10 0x1012c0d0
	// MxCore::`scalar deleting destructor'

private:
	static MxU32 g_nextCoreId;

	MxU32 m_id; // 0x04
};

// SYNTHETIC: BETA10 0x10096940
// MxCore::operator=

#endif // MXCORE_H
