#ifndef MXDSOBJECT_H
#define MXDSOBJECT_H

#include "mxatom.h"
#include "mxcore.h"
#include "mxutilitylist.h"

class MxDSFile;
class MxDSObject;
class MxPresenter;

class MxDSObjectList : public MxUtilityList<MxDSObject*> {
public:
	MxDSObject* FindAndErase(MxDSObject* p_action) {
		return FindInternal(p_action, TRUE);
	}

	MxDSObject* Find(MxDSObject* p_action) {
		return FindInternal(p_action, FALSE);
	}

private:
	MxDSObject* FindInternal(MxDSObject* p_action, MxBool p_delete);
};

class MxDSObject : public MxCore {
public:
	enum Type {
		e_object = 0,
		e_action,
		e_mediaAction,
		e_anim,
		e_sound,
		e_multiAction,
		e_serialAction,
		e_parallelAction,
		e_event,
		e_selectAction,
		e_still,
		e_objectAction,
	};

	MxDSObject();
	~MxDSObject() override;

	void CopyFrom(MxDSObject& p_dsObject);
	MxDSObject(MxDSObject& p_dsObject);
	MxDSObject& operator=(MxDSObject& p_dsObject);

	void SetObjectName(const char* p_objectName);
	void SetSourceName(const char* p_sourceName);

	static const char* ClassName() { return "MxDSObject"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDSObject::ClassName()) || MxCore::IsA(p_name);
	}

	virtual undefined4 VTable0x14();
	virtual MxU32 GetSizeOnDisk();
	virtual void Deserialize(MxU8*& p_source, MxS16 p_unk0x24);

	virtual void SetAtomId(MxAtomId p_atomId) { m_atomId = p_atomId; }

	Type GetType() const { return (Type) m_type; }

	const char* GetSourceName() const { return m_sourceName; }

	const char* GetObjectName() const { return m_objectName; }

	MxU32 GetObjectId() { return m_objectId; }

	const MxAtomId& GetAtomId() { return m_atomId; }

	MxS16 GetUnknown24() { return m_unk0x24; }
	MxPresenter* GetUnknown28() { return m_unk0x28; }

	void SetType(Type p_type) { m_type = p_type; }

	void SetObjectId(MxU32 p_objectId) { m_objectId = p_objectId; }

	void SetUnknown24(MxS16 p_unk0x24) { m_unk0x24 = p_unk0x24; }

	void SetUnknown28(MxPresenter* p_unk0x28) { m_unk0x28 = p_unk0x28; }

	void ClearAtom() { m_atomId.Clear(); }

	// MxDSObject::`scalar deleting destructor'

protected:
	MxU32 m_sizeOnDisk;
	MxU16 m_type;
	char* m_sourceName;
	undefined4 m_unk0x14;
	char* m_objectName;
	MxU32 m_objectId;
	MxAtomId m_atomId;
	MxS16 m_unk0x24;
	MxPresenter* m_unk0x28;
};

MxDSObject* DeserializeDSObjectDispatch(MxU8*&, MxS16);
MxDSObject* CreateStreamObject(MxDSFile*, MxS16);

// MxUtilityList<MxDSObject *>::PopFront

#endif // MXDSOBJECT_H
