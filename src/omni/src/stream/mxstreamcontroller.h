#ifndef MXSTREAMCONTROLLER_H
#define MXSTREAMCONTROLLER_H

#include "mxatom.h"
#include "mxcore.h"
#include "mxcriticalsection.h"
#include "mxdsobject.h"
#include "mxdssubscriber.h"
#include "mxnextactiondatastart.h"

class MxDSAction;
class MxDSStreamingAction;
class MxStreamProvider;

class MxNextActionDataStartList : public MxUtilityList<MxNextActionDataStart*> {
public:
	MxNextActionDataStart* Find(MxU32 p_id, MxS16 p_value);
	MxNextActionDataStart* FindAndErase(MxU32 p_id, MxS16 p_value);
};

class MxStreamController : public MxCore {
public:
	MxStreamController();
	~MxStreamController() override;

	static const char* ClassName() { return "MxStreamController"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxStreamController::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	virtual MxResult Open(const char* p_filename);

	virtual MxResult VTable0x18(undefined4, undefined4) { return FAILURE; }

	virtual MxResult VTable0x1c(undefined4, undefined4) { return FAILURE; }

	virtual MxResult VTable0x20(MxDSAction* p_action);
	virtual MxResult VTable0x24(MxDSAction* p_action);

	virtual MxDSStreamingAction* VTable0x28() { return NULL; }

	virtual MxResult VTable0x2c(MxDSAction* p_action, MxU32 p_bufferval);
	virtual MxResult VTable0x30(MxDSAction* p_action);

	void AddSubscriber(MxDSSubscriber* p_subscriber);
	void RemoveSubscriber(MxDSSubscriber* p_subscriber);
	MxResult FUN_100c1800(MxDSAction* p_action, MxU32 p_val);
	MxResult FUN_100c1a00(MxDSAction* p_action, MxU32 p_offset);
	MxPresenter* FUN_100c1e70(MxDSAction& p_action);
	MxResult FUN_100c1f00(MxDSAction* p_action);
	MxBool IsStoped(MxDSObject* p_obj);
	MxResult InsertActionToList54(MxDSAction* p_action);
	MxNextActionDataStart*
	FindNextActionDataStartFromStreamingAction(MxDSStreamingAction* p_action);

	MxAtomId& GetAtom() { return m_atom; }
	MxStreamProvider* GetProvider() { return m_provider; }
	MxDSObjectList& GetUnk0x3c() { return m_unk0x3c; }
	MxDSObjectList& GetUnk0x54() { return m_unk0x54; }
	MxDSSubscriberList& GetSubscriberList() { return m_subscribers; }

protected:
	MxCriticalSection m_criticalSection;
	MxAtomId m_atom;
	MxStreamProvider* m_provider;
	undefined4* m_unk0x2c;
	MxDSSubscriberList m_subscribers;
	MxDSObjectList m_unk0x3c;
	MxNextActionDataStartList m_nextActionList;
	MxDSObjectList m_unk0x54;
	MxDSAction* m_action0x60;
};

// list<MxDSObject *,allocator<MxDSObject *> >::~list<MxDSObject
// *,allocator<MxDSObject *> >

// list<MxDSSubscriber *,allocator<MxDSSubscriber *> >::~list<MxDSSubscriber
// *,allocator<MxDSSubscriber *> >

// list<MxDSSubscriber *,allocator<MxDSSubscriber *> >::_Buynode

// clang-format off

// list<MxNextActionDataStart *,allocator<MxNextActionDataStart *> >::~list<MxNextActionDataStart *,allocator<MxNextActionDataStart *> >
// clang-format on

// list<MxNextActionDataStart *,allocator<MxNextActionDataStart *> >::_Buynode

// MxStreamController::`scalar deleting destructor'

// MxDSSubscriberList::~MxDSSubscriberList

// MxDSObjectList::~MxDSObjectList

// MxNextActionDataStartList::~MxNextActionDataStartList

// MxUtilityList<MxDSSubscriber *>::~MxUtilityList<MxDSSubscriber *>

// MxUtilityList<MxDSObject *>::~MxUtilityList<MxDSObject *>

// MxUtilityList<MxNextActionDataStart *>::~MxUtilityList<MxNextActionDataStart
// *>

// List<MxDSSubscriber *>::~List<MxDSSubscriber *>

// List<MxDSObject *>::~List<MxDSObject *>

// List<MxNextActionDataStart *>::~List<MxNextActionDataStart *>

// list<MxDSObject *,allocator<MxDSObject *> >::insert

// MxUtilityList<MxDSSubscriber *>::PushBack

// MxUtilityList<MxDSSubscriber *>::Remove

#endif // MXSTREAMCONTROLLER_H
