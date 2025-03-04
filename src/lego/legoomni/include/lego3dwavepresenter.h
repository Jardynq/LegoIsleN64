#ifndef LEGO3DWAVEPRESENTER_H
#define LEGO3DWAVEPRESENTER_H

#include "lego3dsound.h"
#include "mxwavepresenter.h"

class Lego3DWavePresenter : public MxWavePresenter {
public:
	static const char* HandlerClassName() { return "Lego3DWavePresenter"; }

	const char* ClassName() const override { return HandlerClassName(); }

	MxBool IsA(const char* p_name) const override {
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
