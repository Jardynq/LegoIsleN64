#include "mx_core.h"

#include <assert.h>

MxU32 MxCore::g_nextCoreId = 0;

MxCore::MxCore() {
	m_id = g_nextCoreId++;
	assert(g_nextCoreId);
}

MxCore::~MxCore() {
}

MxLong MxCore::Notify(MxParam& p_param) {
	assert(0);
	return 0;
}
