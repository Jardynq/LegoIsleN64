#pragma once

#include "looping_anim_presenter.h"
#include "roi_map_list.h"

class LegoAnimActor;

class LegoLocomotionAnimPresenter : public LegoLoopingAnimPresenter {
public:
	LegoLocomotionAnimPresenter();
	~LegoLocomotionAnimPresenter() override;

	static const char* HandlerClassName() {

		return "LegoLocomotionAnimPresenter";
	}

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ClassName()) ||
			   LegoLoopingAnimPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void StartingTickle() override;
	void StreamingTickle() override;
	MxResult AddToManager() override;
	void Destroy() override;
	void EndAction() override;
	void PutFrame() override;
	MxResult CreateAnim(MxStreamChunk* p_chunk) override;

	// LegoLocomotionAnimPresenter::`scalar deleting destructor'

	void FUN_1006d680(LegoAnimActor* p_actor, MxFloat p_value);

	void DecrementUnknown0xd4() {
		if (m_unk0xd4) {
			--m_unk0xd4;
		}
	}

	undefined2 GetUnknown0xd4() { return m_unk0xd4; }

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);

	undefined4 m_unk0xc0;
	undefined4* m_unk0xc4;
	LegoROIMapList* m_roiMapList;
	MxS32 m_unk0xcc;
	MxS32 m_unk0xd0;
	undefined2 m_unk0xd4;
};

