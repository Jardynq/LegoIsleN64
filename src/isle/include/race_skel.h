#pragma once

#include "anim_actor.h"

class RaceSkel : public LegoAnimActor {
public:
	RaceSkel();
	~RaceSkel() override;

	void ParseAction(char* p_extra) override;

	MxResult FUN_1001c360(float p_und, Matrix4& p_transform) override;

	virtual void FUN_10071c80(Vector3& p_vec);

	void GetCurrentAnimData(
		float* p_outCurAnimPosition,
		float* p_outCurAnimDuration
	);

	// RaceSkel::`scalar deleting destructor'

private:
	float m_animPosition;
};

// RaceSkel::`vbtable'

