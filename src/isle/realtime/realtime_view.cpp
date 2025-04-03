#include "realtime_view.h"

#include <math.h>

float g_userMaxLodPower;

float g_userMaxBase = 4.0f;

float g_userMaxLod = 3.6f;

float g_partsThreshold = 1000.0f;

RealtimeView::RealtimeView() {
	UpdateMaxLOD();
}

RealtimeView::~RealtimeView() {
}

void RealtimeView::SetUserMaxLOD(float p_lod) {
	g_userMaxLod = p_lod;
	UpdateMaxLOD();
}

void RealtimeView::SetPartsThreshold(float p_threshold) {
	g_partsThreshold = p_threshold;
}

float RealtimeView::GetUserMaxLOD() {
	return g_userMaxLod;
}

float RealtimeView::GetPartsThreshold() {
	return g_partsThreshold;
}

void RealtimeView::UpdateMaxLOD() {
	g_userMaxLodPower = pow(g_userMaxBase, -g_userMaxLod);
}
