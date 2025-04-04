#pragma once

#include "mx_atom.h"
#include "mx_core.h"

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

private:
	MxAtomId m_idMxPresenter;
	MxAtomId m_idMxCompositePresenter;
	MxAtomId m_idMxVideoPresenter;
	MxAtomId m_idMxFlcPresenter;
	MxAtomId m_idMxSmkPresenter;
	MxAtomId m_idMxStillPresenter;
	MxAtomId m_idMxWavePresenter;
	MxAtomId m_idMxMIDIPresenter;
	MxAtomId m_idMxEventPresenter;
	MxAtomId m_idMxLoopingFlcPresenter;
	MxAtomId m_idMxLoopingSmkPresenter;
	MxAtomId m_idMxLoopingMIDIPresenter;
};
