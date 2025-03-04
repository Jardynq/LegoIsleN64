#ifndef LEGOCARBUILDPRESENTER_H
#define LEGOCARBUILDPRESENTER_H

#include "anim/legoanim.h"
#include "legoanimpresenter.h"

class LegoCarBuildAnimPresenter : public LegoAnimPresenter {
public:
	enum { c_bit1 = 0x01 };

	struct UnknownListEntry {

		UnknownListEntry() {
			m_name = NULL;
			m_wiredName = NULL;
			m_objectId = 0;
		}

		// variable name verified by BETA10 0x10071b56
		LegoChar* m_name;
		// variable name verified by BETA10 0x100719f0
		LegoChar* m_wiredName;
		// variable name guessed based on the setter at LEGO1 0x0x10079dc0 and
		// its use in LEGO1 0x10024890
		MxS16 m_objectId;
	};

	LegoCarBuildAnimPresenter();
	~LegoCarBuildAnimPresenter() override;

	static const char* HandlerClassName() {

		return "LegoCarBuildAnimPresenter";
	}

	void RepeatingTickle() override {}

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, LegoCarBuildAnimPresenter::ClassName()) ||
			   LegoAnimPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StreamingTickle() override;
	void EndAction() override;
	void PutFrame() override;

	virtual MxResult Serialize(LegoStorage* p_storage);

	void FUN_10079050(MxS16 p_index);
	void SwapNodesByName(LegoChar* p_param1, LegoChar* p_param2);
	void FUN_10079160();
	void FUN_100795d0(LegoChar* p_param);
	void FUN_10079680(LegoChar* p_param);
	LegoAnimNodeData*
	FindNodeDataByName(LegoTreeNode* p_treeNode, const LegoChar* p_name);
	LegoTreeNode*
	FindNodeByName(LegoTreeNode* p_treeNode, const LegoChar* p_name);
	void FUN_10079790(const LegoChar* p_name);
	void RotateAroundYAxis(MxFloat p_angle);
	MxBool FUN_10079c30(const LegoChar* p_name);
	MxBool PartIsPlaced(const LegoChar* p_name);
	void FUN_10079a90();
	MxBool StringEqualsPlatform(const LegoChar* p_string);
	MxBool StringEqualsShelf(const LegoChar* p_string);
	MxBool StringEndsOnY(const LegoChar* p_string);
	MxBool StringDoesNotEndOnZero(const LegoChar* p_string);
	const LegoChar* GetWiredNameByPartName(const LegoChar* p_name);
	void SetPartObjectIdByName(const LegoChar* p_name, MxS16 p_objectId);

	void SetUnknown0xbc(undefined2 p_unk0xbc) { m_unk0xbc = p_unk0xbc; }

	MxMatrix& GetUnknown0xe0() { return m_unk0xe0; }

	MxBool StringEndsOnW(LegoChar* p_param);
	MxBool StringEndsOnYOrN(const LegoChar* p_string);

	const BoundingSphere& FUN_10079e20();

	const LegoChar* GetWiredNameOfLastPlacedPart() {
		return m_parts[m_placedPartCount].m_wiredName;
	}

	MxS16 GetNumberOfParts() { return m_numberOfParts; }
	MxS16 GetPlacedPartCount() { return m_placedPartCount; }

	MxBool AllPartsPlaced() {
		// this function differs in BETA10
		return m_placedPartCount == m_numberOfParts;
	}

	// LegoCarBuildAnimPresenter::`scalar deleting destructor'

private:
	void Beta10Inline0x100733d0();

	MxU16 m_unk0xbc;
	// variable name verified by BETA10 0x1007184f
	MxS16 m_numberOfParts;
	// name derived from LegoVehicleBuildState, field 0x4f
	MxS16 m_placedPartCount;
	LegoAnimNodeData* m_unk0xc4;
	LegoAnim m_unk0xc8;
	MxMatrix m_unk0xe0;
	// variable name verified by BETA10 0x100719f0
	UnknownListEntry* m_parts;
	MxFloat m_unk0x12c;
	MxFloat m_unk0x130;
	MxFloat m_unk0x134;
	MxFloat m_unk0x138;
	MxULong m_unk0x13c;
	LegoEntity* m_unk0x140;
	MxS32 m_unk0x144;
	MxS32 m_unk0x148;
	// name verified by BETA10 0x10070d63
	LegoChar* m_mainSourceId;
};

#endif // LEGOCARBUILDPRESENTER_H
