#pragma once

#include "mxcriticalsection.h"
#include "mx_ds_action.h"
#include "mx_stream_provider.h"
#include "mxthread.h"

class MxDiskStreamProvider;
class MxDSStreamingAction;

class MxDiskStreamProviderThread : public MxThread {
public:
	MxDiskStreamProviderThread() : MxThread() { m_target = NULL; }

	MxResult Run() override;
	MxResult StartWithTarget(MxDiskStreamProvider* p_target);
};

class MxDiskStreamProvider : public MxStreamProvider {
public:
	MxDiskStreamProvider();
	~MxDiskStreamProvider() override;

	static const char* ClassName() { return "MxDiskStreamProvider"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDiskStreamProvider::ClassName()) ||
			   MxStreamProvider::IsA(p_name);
	}

	MxResult WaitForWorkToComplete();
	MxResult FUN_100d1780(MxDSStreamingAction* p_action);
	void PerformWork();
	static MxBool FUN_100d1af0(MxDSStreamingAction* p_action);
	MxResult FUN_100d1b20(MxDSStreamingAction* p_action);

	MxResult SetResourceToGet(MxStreamController* p_resource) override;
	MxU32 GetFileSize() override;
	MxS32 GetStreamBuffersNum() override;
	void VTable0x20(MxDSAction* p_action) override;
	MxU32 GetLengthInDWords() override;
	MxU32* GetBufferForDWords() override;

private:
	MxDiskStreamProviderThread m_thread;
	MxSemaphore m_busySemaphore;
	MxBool m_remainingWork;
	MxBool m_unk0x35;
	MxCriticalSection m_criticalSection;
	MxDSObjectList m_list;
};

// MxDiskStreamProviderThread::`scalar deleting destructor'

// MxDiskStreamProviderThread::~MxDiskStreamProviderThread

// MxDiskStreamProvider::`scalar deleting destructor'

