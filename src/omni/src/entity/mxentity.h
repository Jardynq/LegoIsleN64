#ifndef MXENTITY_H
#define MXENTITY_H

#include "mxatom.h"
#include "mxcore.h"
#include "mxdsaction.h"

class MxEntity : public MxCore {
public:
	MxEntity() { m_entityId = -1; }

	~MxEntity() override {}

	static const char* ClassName() { return "MxEntity"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxEntity::ClassName()) || MxCore::IsA(p_name);
	}

	virtual MxResult Create(MxS32 p_entityId, const MxAtomId& p_atomId) {
		m_entityId = p_entityId;
		m_atomId = p_atomId;
		return SUCCESS;
	}

	MxResult Create(MxDSAction& p_dsAction) {
		m_entityId = p_dsAction.GetObjectId();
		m_atomId = p_dsAction.GetAtomId();
		return SUCCESS;
	}

	MxS32 GetEntityId() { return m_entityId; }

	MxAtomId& GetAtomId() { return m_atomId; }

	void SetEntityId(MxS32 p_entityId) { m_entityId = p_entityId; }
	void SetAtomId(const MxAtomId& p_atomId) { m_atomId = p_atomId; }

protected:
	MxS32 m_entityId;
	MxAtomId m_atomId;
};

#endif // MXENTITY_H
