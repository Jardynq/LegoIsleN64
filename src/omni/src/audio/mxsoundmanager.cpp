#include "mxsoundmanager.h"

#include "mxautolock.h"
#include "mxdsaction.h"
#include "mxmisc.h"
#include "mxomni.h"
#include "mxpresenter.h"
#include "mxticklemanager.h"
#include "mxwavepresenter.h"
#include <cstddef>

MxS32 g_volumeAttenuation[100] = {
	-6643, -5643, -5058, -4643, -4321, -4058, -3836, -3643, -3473, -3321,
	-3184, -3058, -2943, -2836, -2736, -2643, -2556, -2473, -2395, -2321,
	-2251, -2184, -2120, -2058, -2000, -1943, -1888, -1836, -1785, -1736,
	-1689, -1643, -1599, -1556, -1514, -1473, -1434, -1395, -1358, -1321,
	-1286, -1251, -1217, -1184, -1152, -1120, -1089, -1058, -1029, -1000,
	-971,  -943,  -915,  -888,  -862,  -836,  -810,  -785,  -761,  -736,
	-713,  -689,  -666,  -643,  -621,  -599,  -577,  -556,  -535,  -514,
	-494,  -473,  -454,  -434,  -415,  -395,  -377,  -358,  -340,  -321,
	-304,  -286,  -268,  -251,  -234,  -217,  -200,  -184,  -168,  -152,
	-136,  -120,  -104,  -89,   -74,   -58,   -43,   -29,   -14,   0};

MxSoundManager::MxSoundManager() {
	Init();
}

MxSoundManager::~MxSoundManager() {
	Destroy(TRUE);
}

void MxSoundManager::Init() {
}

void MxSoundManager::Destroy(MxBool p_fromDestructor) {
	TickleManager()->UnregisterClient(this);

	Init();

	if (!p_fromDestructor) {
		MxAudioManager::Destroy();
	}
}

MxResult MxSoundManager::Create(MxU32 p_frequencyMS) {
	MxResult status = FAILURE;

	if (MxAudioManager::Create() != SUCCESS) {
		goto done;
	}

	TickleManager()->RegisterClient(this, p_frequencyMS);

	status = SUCCESS;

done:
	if (status != SUCCESS) {
		Destroy();
	}


	return status;
}

void MxSoundManager::Destroy() {
	Destroy(FALSE);
}

void MxSoundManager::SetVolume(MxS32 p_volume) {
	MxAudioManager::SetVolume(p_volume);

	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(m_presenters);

	while (cursor.Next(presenter)) {
		((MxAudioPresenter*) presenter)
			->SetVolume(((MxAudioPresenter*) presenter)->GetVolume());
	}

}

MxPresenter*
MxSoundManager::FUN_100aebd0(const MxAtomId& p_atomId, MxU32 p_objectId) {
	AUTOLOCK(m_criticalSection);

	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(m_presenters);

	while (cursor.Next(presenter)) {
		if (presenter->GetAction()->GetAtomId().GetInternal() ==
				p_atomId.GetInternal() &&
			presenter->GetAction()->GetObjectId() == p_objectId) {
			return presenter;
		}
	}

	return NULL;
}

MxS32 MxSoundManager::GetAttenuation(MxU32 p_volume) {
	// The unit for p_volume is percent, rounded to integer.
	// Convert to DSOUND attenuation units: -10000 (silent) to 0 (loudest).
	if (p_volume == 0) {
		return -10000;
	}

	return g_volumeAttenuation[p_volume - 1];
}

void MxSoundManager::Pause() {
	AUTOLOCK(m_criticalSection);

	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(m_presenters);

	while (cursor.Next(presenter)) {
		if (presenter->IsA("MxWavePresenter")) {
			((MxWavePresenter*) presenter)->Pause();
		}
	}
}

void MxSoundManager::Resume() {
	AUTOLOCK(m_criticalSection);

	MxPresenter* presenter = nullptr;
	MxPresenterListCursor cursor(m_presenters);

	while (cursor.Next(presenter)) {
		if (presenter->IsA("MxWavePresenter")) {
			((MxWavePresenter*) presenter)->Resume();
		}
	}
}
