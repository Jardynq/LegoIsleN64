#pragma once

#include "mx_core.h"

class MxNotificationParam;

class MxNotification {
public:
	MxNotification(MxCore* p_target, const MxNotificationParam& p_param);
	~MxNotification();

	MxCore* GetTarget() { return m_target; }
	MxNotificationParam* GetParam() { return m_param; }

private:
	MxCore* m_target;
	MxNotificationParam* m_param;
};

class MxIdList : public list<MxU32> {};

class MxNotificationPtrList : public list<MxNotification*> {};

class MxNotificationManager : public MxCore {
private:
	MxNotificationPtrList* m_queue;
	MxNotificationPtrList* m_sendList;
	MxS32 m_unk0x2c;
	MxIdList m_listenerIds;
	MxBool m_active;

public:
	MxNotificationManager();
	~MxNotificationManager() override;

	MxResult Tickle() override;

	virtual MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread);
	void Register(MxCore* p_listener);
	void Unregister(MxCore* p_listener);
	MxResult Send(MxCore* p_listener, const MxNotificationParam& p_param);

	MxNotificationPtrList* GetQueue() { return m_queue; }

	void SetActive(MxBool p_active) { m_active = p_active; }

	MxBool IsEmpty() const { return m_queue ? m_queue->empty() : TRUE; }

	// MxNotificationManager::`scalar deleting destructor'

private:
	void FlushPending(MxCore* p_listener);
};

// list<unsigned int,allocator<unsigned int> >::~list<unsigned
// int,allocator<unsigned int> >

// MxIdList::~MxIdList

// List<unsigned int>::~List<unsigned int>

// List<MxNotification *>::~List<MxNotification *>

// list<MxNotification *,allocator<MxNotification *> >::~list<MxNotification
// *,allocator<MxNotification *> >

// list<MxNotification *,allocator<MxNotification *> >::begin

// list<MxNotification *,allocator<MxNotification *> >::insert

// list<MxNotification *,allocator<MxNotification *> >::erase

// list<MxNotification *,allocator<MxNotification *> >::_Buynode

// MxNotificationPtrList::~MxNotificationPtrList

// list<MxNotification *,allocator<MxNotification *> >::empty
