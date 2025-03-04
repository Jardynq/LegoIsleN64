#ifndef ACT2BRICK_H
#define ACT2BRICK_H

#include "legopathactor.h"

class Act2Brick : public LegoPathActor {
public:
	Act2Brick();
	~Act2Brick() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	const char* ClassName() const override { return "Act2Brick"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, Act2Brick::ClassName()) ||
			   LegoEntity::IsA(p_name);
	}

	MxResult HitActor(LegoPathActor* p_actor, MxBool) override;

	// Act2Brick::`scalar deleting destructor'

	MxResult Create(MxS32 p_index);
	void Remove();
	void FUN_1007a670(
		MxMatrix& p_param1,
		MxMatrix& p_param2,
		LegoPathBoundary* p_boundary
	);
	void PlayWhistleSound();
	void StopWhistleSound();
	void Mute(MxBool p_muted);

private:
	static const LegoChar* g_lodNames[];
	static MxLong g_lastHitActorTime;

	LegoCacheSound* m_whistleSound;
	undefined m_unk0x158[0x0c];
	undefined4 m_unk0x164;
	Mx3DPointFloat m_unk0x168;
	Mx3DPointFloat m_unk0x17c;
	MxS32 m_unk0x190;
};

#endif // ACT2BRICK_H
