#ifndef MXSTREAMPROVIDER_H
#define MXSTREAMPROVIDER_H

#include "mxcore.h"

class MxStreamController;
class MxDSAction;
class MxDSFile;

class MxStreamProvider : public MxCore {
public:
	MxStreamProvider() : m_pLookup(NULL), m_pFile(NULL) {}

	const char* ClassName() const override { return "MxStreamProvider"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, MxStreamProvider::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	virtual MxResult SetResourceToGet(MxStreamController* p_pLookup) {
		m_pLookup = p_pLookup;
		return SUCCESS;
	}

	virtual MxU32 GetFileSize() = 0;
	virtual MxS32 GetStreamBuffersNum() = 0;

	virtual void VTable0x20(MxDSAction* p_action) {}

	virtual MxU32 GetLengthInDWords() = 0;
	virtual MxU32* GetBufferForDWords() = 0;

protected:
	MxStreamController* m_pLookup;
	MxDSFile* m_pFile;
};

// MxStreamProvider::`scalar deleting destructor'

// MxStreamProvider::~MxStreamProvider

#endif // MXSTREAMPROVIDER_H
