#ifndef MXTRANSITIONMANAGER_H
#define MXTRANSITIONMANAGER_H

#include "mxcore.h"

#include <ddraw.h>

class MxVideoPresenter;

class MxTransitionManager : public MxCore {
public:
	MxTransitionManager();
	~MxTransitionManager() override;

	void SetWaitIndicator(MxVideoPresenter* p_waitIndicator);

	MxResult Tickle() override;

	static const char* ClassName() { return "MxTransitionManager"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxTransitionManager::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	virtual MxResult GetDDrawSurfaceFromVideoManager();

	enum TransitionType {
		e_idle = 0, // name verified by BETA10 0x100ec4e6
		e_noAnimation,
		e_dissolve,
		e_mosaic,
		e_wipeDown,
		e_windows,
		e_broken // Unknown what this is supposed to be, it locks the game up
	};

	MxResult StartTransition(
		TransitionType p_animationType,
		MxS32 p_speed,
		MxBool p_doCopy,
		MxBool p_playMusicInAnim
	);

	TransitionType GetTransitionType() { return m_mode; }

	// MxTransitionManager::`scalar deleting destructor'

private:
	void EndTransition(MxBool p_notifyWorld);
	void NoTransition();
	void DissolveTransition();
	void MosaicTransition();
	void WipeDownTransition();
	void WindowsTransition();
	void BrokenTransition();

	void SubmitCopyRect(LPDDSURFACEDESC p_ddsc);
	void SetupCopyRect(LPDDSURFACEDESC p_ddsc);

	MxVideoPresenter* m_waitIndicator;
	RECT m_copyRect;
	MxU8* m_copyBuffer;
	FlagBitfield m_copyFlags;
	undefined4 m_unk0x24;
	FlagBitfield m_unk0x28;
	// name verified by BETA10 0x100ec4e6
	TransitionType m_mode;
	LPDIRECTDRAWSURFACE m_ddSurface;
	MxU16 m_animationTimer;
	MxU16 m_columnOrder[640];
	MxU16 m_randomShift[480];
	MxULong m_systemTime;
	MxS32 m_animationSpeed;
};

#endif // MXTRANSITIONMANAGER_H
