#ifndef LEGOANIMMMPRESENTER_H
#define LEGOANIMMMPRESENTER_H

// MxDSActionListCursor needs to be included before std::list
// clang-format off
#include "mxdsmultiaction.h"
// clang-format on
#include "mxcompositepresenter.h"

class LegoAnimPresenter;
class LegoWorld;
class LegoROI;
struct LegoTranInfo;
class MxMatrix;

class LegoAnimMMPresenter : public MxCompositePresenter {
public:
	enum { e_unk0, e_unk1, e_unk2, e_unk3, e_unk4, e_unk5, e_unk6, e_unk7 };

	LegoAnimMMPresenter();
	~LegoAnimMMPresenter() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* HandlerClassName() { return "LegoAnimMMPresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoAnimMMPresenter::ClassName()) ||
			   MxCompositePresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void StreamingTickle() override;
	void RepeatingTickle() override;
	void DoneTickle() override;
	void ParseExtra() override;
	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action)
		override;
	void EndAction() override;
	void VTable0x60(MxPresenter* p_presenter) override;

	// LegoAnimMMPresenter::`scalar deleting destructor'
	MxBool FUN_1004b830();
	void FUN_1004b840();
	MxBool FUN_1004b8b0();
	void FUN_1004b8c0();

	LegoAnimPresenter* GetPresenter() { return m_presenter; }

private:
	MxBool FUN_1004b450();
	MxBool FUN_1004b530(MxLong p_time);
	MxBool FUN_1004b570(MxLong p_time);
	MxBool FUN_1004b580(MxLong p_time);
	MxBool FUN_1004b5b0(MxLong p_time);
	MxBool FUN_1004b600(MxLong p_time);
	MxBool FUN_1004b610(MxLong p_time);
	MxBool FUN_1004b6b0(MxLong p_time);
	MxBool FUN_1004b6d0(MxLong p_time);

	LegoAnimPresenter* m_presenter;
	MxLong m_unk0x50;
	undefined4 m_unk0x54;
	MxU8 m_unk0x58;
	MxU8 m_unk0x59;
	MxU32 m_animmanId;
	LegoTranInfo* m_tranInfo;
	LegoWorld* m_unk0x64;
	MxMatrix* m_unk0x68;
	LegoROI** m_roiMap;
	MxU32 m_roiMapSize;
};

#endif // LEGOANIMMMPRESENTER_H
