#pragma once

#include "mx_ds_buffer.h"
#include "mx_stream_controller.h"

#include <string.h>

class MxDSStreamingAction;

class MxDiskStreamController : public MxStreamController {
public:
	MxDiskStreamController();
	~MxDiskStreamController() override;

	MxResult Tickle() override;

	static const char* ClassName() { return "MxDiskStreamController"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxDiskStreamController::ClassName()) ||
			   MxStreamController::IsA(p_name);
	}

	MxResult Open(const char* p_filename) override;
	MxResult VTable0x18(undefined4, undefined4) override;
	MxResult VTable0x20(MxDSAction* p_action) override;
	MxResult VTable0x24(MxDSAction* p_action) override;
	MxDSStreamingAction* VTable0x28() override;
	MxResult StopAction(MxDSAction* p_action) override;
	virtual MxResult VTable0x34(undefined4);

	MxBool GetUnk0xc4() const { return m_unk0xc4; }

	MxResult FUN_100c7890(MxDSStreamingAction* p_action);
	void Cleanup(MxDSStreamingAction* p_action);
	void FUN_100c7f40(MxDSStreamingAction* p_streamingaction);
	void FUN_100c8120(MxDSAction* p_action);
	void InsertToList74(MxDSBuffer* p_buffer);
	void FUN_100c8670(MxDSStreamingAction* p_streamingAction);

private:
	MxDSObjectList m_list0x64;
	MxBool m_unk0x70;
	list<MxDSBuffer*> m_list0x74;
	MxDSObjectList m_list0x80;
	undefined2 m_unk0x8c;
	MxDSObjectList m_list0x90;
	MxDSObjectList m_list0xb8;
	MxBool m_unk0xc4;
	void FUN_100c7970();
	void FUN_100c7ce0(MxDSBuffer* p_buffer);
	MxResult FUN_100c7d10();
	void FUN_100c7980();
	MxDSStreamingAction* FUN_100c7db0();
	MxResult FUN_100c8360(MxDSStreamingAction* p_action);
	void FUN_100c8540();
	void FUN_100c8720();
};
