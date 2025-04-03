#pragma once

#include "mx_composite_presenter.h"

class LegoControlManagerNotificationParam;
class MxVideoPresenter;

class MxControlPresenter : public MxCompositePresenter {
public:
	MxControlPresenter();
	~MxControlPresenter() override;

	void RepeatingTickle() override {}

	MxBool VTable0x64(undefined4 p_undefined) override { return m_unk0x50; }

	virtual void VTable0x68(MxBool p_unk0x50) { m_unk0x50 = p_unk0x50; }

	static const char* ClassName() { return "MxControlPresenter"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxControlPresenter::ClassName()) ||
			   MxCompositePresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void ParseExtra() override;
	MxResult AddToManager() override;
	MxResult StartAction(MxStreamController*, MxDSAction*) override;
	void EndAction() override;
	MxBool HasTickleStatePassed(TickleState p_tickleState) override;
	void Enable(MxBool p_enable) override;
	virtual void VTable0x6c(MxS16 p_unk0x4e);

	MxBool FUN_10044480(
		LegoControlManagerNotificationParam* p_param,
		MxPresenter* p_presenter
	);
	MxBool FUN_10044270(MxS32 p_x, MxS32 p_y, MxVideoPresenter* p_presenter);

	MxS16 GetUnknown0x4e() { return m_unk0x4e; }

private:
	undefined2 m_unk0x4c;
	MxS16 m_unk0x4e;
	MxBool m_unk0x50;
	undefined2 m_unk0x52;
	undefined2 m_unk0x54;
	undefined2 m_unk0x56;
	MxS16* m_unk0x58;
};

// MxControlPresenter::`scalar deleting destructor'

