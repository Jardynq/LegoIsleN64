#ifndef MXOBJECTFACTORY_H
#define MXOBJECTFACTORY_H

#include "mx_atom.h"
#include "mx_core.h"

#define FOR_MXOBJECTFACTORY_OBJECTS(X)                                         \
	X(MxPresenter)                                                             \
	X(MxCompositePresenter)                                                    \
	X(MxVideoPresenter)                                                        \
	X(MxFlcPresenter)                                                          \
	X(MxSmkPresenter)                                                          \
	X(MxStillPresenter)                                                        \
	X(MxWavePresenter)                                                         \
	X(MxMIDIPresenter)                                                         \
	X(MxEventPresenter)                                                        \
	X(MxLoopingFlcPresenter)                                                   \
	X(MxLoopingSmkPresenter)                                                   \
	X(MxLoopingMIDIPresenter)

class MxObjectFactory : public MxCore {
public:
	MxObjectFactory();

	static const char* ClassName() { return "MxObjectFactory"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxObjectFactory::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	virtual MxCore* Create(const char* p_name);
	virtual void Destroy(MxCore* p_object);

	// MxObjectFactory::`scalar deleting destructor'

	// MxObjectFactory::~MxObjectFactory

private:
#define X(V) MxAtomId m_id##V;
	FOR_MXOBJECTFACTORY_OBJECTS(X)
#undef X
};

#endif // MXOBJECTFACTORY_H
