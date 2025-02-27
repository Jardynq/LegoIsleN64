#include "mxobjectfactory.h"

#include "utils.h"
#include "mxcompositepresenter.h"
#include "mxeventpresenter.h"
#include "mxflcpresenter.h"
#include "mxloopingflcpresenter.h"
#include "mxloopingmidipresenter.h"
#include "mxloopingsmkpresenter.h"
#include "mxmidipresenter.h"
#include "mxpresenter.h"
#include "mxsmkpresenter.h"
#include "mxstillpresenter.h"
#include "mxvideopresenter.h"
#include "mxwavepresenter.h"


// FUNCTION: LEGO1 0x100b0d80
MxObjectFactory::MxObjectFactory() {
#define X(V) m_id##V = MxAtomId(#V, e_exact);
	FOR_MXOBJECTFACTORY_OBJECTS(X)
#undef X
}

// FUNCTION: LEGO1 0x100b12c0
// FUNCTION: BETA10 0x10143177
MxCore* MxObjectFactory::Create(const char* p_name) {
	MxCore* object = NULL;
	MxAtomId atom(p_name, e_exact);

	if (0) {
	}
#define X(V)                                                                                                           \
	else if (m_id##V == atom)                                                                                          \
	{                                                                                                                  \
		object = new V;                                                                                                \
	}
	FOR_MXOBJECTFACTORY_OBJECTS(X)
#undef X
		return object;
}

// FUNCTION: LEGO1 0x100b1a30
// FUNCTION: BETA10 0x10143814
void MxObjectFactory::Destroy(MxCore* p_object) {
	delete p_object;
}
