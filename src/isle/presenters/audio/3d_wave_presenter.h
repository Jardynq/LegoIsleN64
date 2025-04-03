#ifndef LEGO3DWAVEPRESENTER_H
#define LEGO3DWAVEPRESENTER_H

#include "3d_sound.h"
#include "mx_wave_presenter.h"

class Lego3DWavePresenter : public MxWavePresenter {
public:
	static const char* HandlerClassName() { return "Lego3DWavePresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Lego3DWavePresenter::ClassName()) ||
			   MxWavePresenter::IsA(p_name);
	}

	void StartingTickle() override;
	void StreamingTickle() override;
	MxResult AddToManager() override;
	void Destroy() override;

	// Lego3DWavePresenter::`scalar deleting destructor'

private:
	undefined m_unk0x6c[4];
	Lego3DSound m_sound;
};

#endif // LEGO3DWAVEPRESENTER_H
