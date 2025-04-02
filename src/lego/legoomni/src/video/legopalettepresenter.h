#ifndef LEGOPALETTEPRESENTER_H
#define LEGOPALETTEPRESENTER_H

#include "mxvideopresenter.h"

class MxPalette;

class LegoPalettePresenter : public MxVideoPresenter {
public:
	LegoPalettePresenter();
	~LegoPalettePresenter() override;

	static const char* HandlerClassName() { return "LegoPalettePresenter"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, ClassName()) || MxVideoPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void Destroy() override;

	MxResult ParsePalette(MxStreamChunk* p_chunk);

	// LegoPalettePresenter::`scalar deleting destructor'

private:
	void Init();
	void Destroy(MxBool p_fromDestructor);

	MxPalette* m_palette;
};

#endif // LEGOPALETTEPRESENTER_H
