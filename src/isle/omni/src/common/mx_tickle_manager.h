#ifndef MXTICKLEMANAGER_H
#define MXTICKLEMANAGER_H

#include "mx_core.h"

class MxTickleClient {
public:
	MxTickleClient(MxCore* p_client, MxTime p_interval);

	MxCore* GetClient() const { return m_client; }

	MxTime GetTickleInterval() const { return m_interval; }

	MxTime GetLastUpdateTime() const { return m_lastUpdateTime; }

	MxU16 GetFlags() const { return m_flags; }

	void SetTickleInterval(MxTime p_interval) { m_interval = p_interval; }

	void SetLastUpdateTime(MxTime p_lastUpdateTime) {
		m_lastUpdateTime = p_lastUpdateTime;
	}

	void SetFlags(MxU16 p_flags) { m_flags = p_flags; }

private:
	MxCore* m_client;
	MxTime m_interval;
	MxTime m_lastUpdateTime;
	MxU16 m_flags;
};

typedef list<MxTickleClient*> MxTickleClientPtrList;

class MxTickleManager : public MxCore {
public:
	MxTickleManager() {}
	~MxTickleManager() override;

	MxResult Tickle() override;
	virtual void RegisterClient(MxCore* p_client, MxTime p_interval);
	virtual void UnregisterClient(MxCore* p_client);
	virtual void SetClientTickleInterval(MxCore* p_client, MxTime p_interval);
	virtual MxTime GetClientTickleInterval(MxCore* p_client);

	// MxTickleManager::`scalar deleting destructor'

private:
	MxTickleClientPtrList m_clients;
};

#define TICKLE_MANAGER_NOT_FOUND 0x80000000

// list<MxTickleClient *,allocator<MxTickleClient *> >::~list<MxTickleClient
// *,allocator<MxTickleClient *> >

// List<MxTickleClient *>::~List<MxTickleClient *>

#endif // MXTICKLEMANAGER_H
