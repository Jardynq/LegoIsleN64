#pragma once

#include "mx_core.h"
#include "mx_ds_action.h"
#include "mx_presenter.h"

class MxAudioPresenter;

class MxBackgroundAudioManager : public MxCore {
public:
	MxBackgroundAudioManager();
	~MxBackgroundAudioManager() override;

	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	static const char* ClassName() {

		return "MxBackgroundAudioManager";
	}

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxBackgroundAudioManager::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	MxBool GetEnabled() { return m_enabled; }

	void StartAction(MxParam& p_param);
	void StopAction(MxParam& p_param);
	MxResult PlayMusic(
		MxDSAction& p_action,
		undefined4 p_speed,
		MxPresenter::TickleState p_tickleState
	);

	void FUN_1007ee70();
	void FUN_1007ef40();
	void FadeInOrFadeOut();

	void Enable(MxBool p_enable);
	virtual MxResult Create(MxAtomId& p_script, MxU32 p_frequencyMS);

	void Init();
	void Stop();
	void LowerVolume();
	void RaiseVolume();
	undefined4 FUN_1007f610(
		MxPresenter* p_unk0x138,
		MxS32 p_speed,
		MxPresenter::TickleState p_tickleState
	);

	// MxBackgroundAudioManager::`scalar deleting destructor'

private:
	MxResult OpenMusic(MxAtomId& p_script);
	void DestroyMusic();

	MxBool m_enabled;
	MxDSAction m_action1;
	MxAudioPresenter* m_unk0xa0;
	MxDSAction m_action2;
	MxAudioPresenter* m_unk0x138;
	// name is inferred from context
	MxPresenter::TickleState m_tickleState;
	// name inferred from parameter p_speed
	MxS32 m_speed;
	MxS32 m_targetVolume;
	MxS16 m_unk0x148;
	MxAtomId m_script;
};

