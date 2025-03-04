#include "raceskel.h"

#include "carrace.h"
#include "legoworld.h"
#include "misc.h"

#include <assert.h>

RaceSkel::RaceSkel() {
	m_animPosition = 0.0f;
}

RaceSkel::~RaceSkel() {
}

MxResult RaceSkel::FUN_1001c360(float p_und, Matrix4& p_transform) {
	p_transform[3][0] = -630.0f;
	p_transform[3][1] = -4.688f;
	p_transform[3][2] = 323.0f;

	m_animPosition = p_und;

	return LegoAnimActor::FUN_1001c360(p_und, p_transform);
}

void RaceSkel::ParseAction(char* p_extra) {
	LegoAnimActor::ParseAction(p_extra);

	// name verified by BETA10 0x100f147d
	CarRace* w = (CarRace*) CurrentWorld();
	assert(w);
	w->SetSkeleton(this);

	assert(m_roi);
	BoundingSphere sphere = m_roi->GetBoundingSphere();
	sphere.Radius() *= 100.0f;
	m_roi->SetBoundingSphere(sphere);
}

void RaceSkel::FUN_10071c80(Vector3& p_vec) {
	p_vec[0] = -630.0f;
	p_vec[1] = -4.688f;
	p_vec[2] = 323.0f;
}

void RaceSkel::GetCurrentAnimData(
	float* p_outCurAnimPosition,
	float* p_outCurAnimDuration
) {
	*p_outCurAnimPosition = m_animPosition;

	assert(m_curAnim >= 0);
	*p_outCurAnimDuration = m_animMaps[m_curAnim]->GetDuration();
}
