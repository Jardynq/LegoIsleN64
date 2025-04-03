#pragma once

#include "mx_core.h"
#include "mx_memory_pool.h"
#include "mx_notification_param.h"
#include "mx_stream_controller.h"

#include <assert.h>

class MxDSObject;

typedef MxMemoryPool<64, 22> MxMemoryPool64;
typedef MxMemoryPool<128, 2> MxMemoryPool128;

class MxStreamerNotification : public MxNotificationParam {
public:
	MxStreamerNotification(
		NotificationId p_type,
		MxCore* p_sender,
		MxStreamController* p_ctrlr
	)
		: MxNotificationParam(p_type, p_sender), m_controller(p_ctrlr) {}

	MxNotificationParam* Clone() const override;

	MxStreamController* GetController() { return m_controller; }

private:
	MxStreamController* m_controller;
};

class MxStreamer : public MxCore {
public:
	enum OpenMode { e_diskStream = 0, e_RAMStream };

	MxStreamer();
	~MxStreamer() override;

	MxStreamController* Open(const char* p_name, MxU16 p_openMode);
	MxLong Close(const char* p_name);

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "MxStreamer"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxStreamer::ClassName()) || MxCore::IsA(p_name);
	}

	virtual MxResult Create();

	MxBool FUN_100b9b30(MxDSObject& p_dsObject);
	MxStreamController* GetOpenStream(const char* p_name);
	void FUN_100b98f0(MxDSAction* p_action);
	MxResult AddStreamControllerToOpenList(MxStreamController* p_stream);
	MxResult FUN_100b99b0(MxDSAction* p_action);
	MxResult DeleteObject(MxDSAction* p_dsAction);

	MxU8* GetMemoryBlock(MxU32 p_blockSize) {
		switch (p_blockSize) {
		case 0x40:
			return m_pool64.Get();

		case 0x80:
			return m_pool128.Get();

		default:
			assert("Invalid block size for memory pool" == NULL);
			break;
		}

		return NULL;
	}

	void ReleaseMemoryBlock(MxU8* p_block, MxU32 p_blockSize) {
		switch (p_blockSize) {
		case 0x40:
			m_pool64.Release(p_block);
			break;

		case 0x80:
			m_pool128.Release(p_block);
			break;

		default:
			assert("Invalid block size for memory pool" == NULL);
			break;
		}
	}

private:
	list<MxStreamController*> m_controllers;
	MxMemoryPool64 m_pool64;
	MxMemoryPool128 m_pool128;
};

// clang-format off


// list<MxStreamController *,allocator<MxStreamController *> >::~list<MxStreamController *,allocator<MxStreamController *> >
// clang-format on

// list<MxStreamController *,allocator<MxStreamController *> >::begin

// list<MxStreamController *,allocator<MxStreamController *> >::end

// list<MxStreamController *,allocator<MxStreamController *>
// >::iterator::operator++

// MxStreamer::`scalar deleting destructor'

// List<MxStreamController *>::~List<MxStreamController *>

// list<MxStreamController *,allocator<MxStreamController *>
// >::iterator::operator*

// MxStreamerNotification::`scalar deleting destructor'

// MxStreamerNotification::~MxStreamerNotification

// list<MxStreamController *,allocator<MxStreamController *>
// >::iterator::operator==

// list<MxStreamController *,allocator<MxStreamController *> >::push_back

// ??9@YAHABViterator@?$list@PAVMxStreamController@@V?$allocator@PAVMxStreamController@@@@@@0@Z

// clang-format off

// ?find@@YA?AViterator@?$list@PAVMxStreamController@@V?$allocator@PAVMxStreamController@@@@@@V12@0ABQAVMxStreamController@@@Z
// clang-format on

