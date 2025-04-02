#ifndef MXPALETTE_H
#define MXPALETTE_H

#include "mxcore.h"

#include <ddraw.h>

class MxPalette : public MxCore {
public:
	MxBool operator==(MxPalette& p_other);
	void Detach();

	MxPalette();
	MxPalette(const RGBQUAD*);
	~MxPalette() override;

	void ApplySystemEntriesToPalette(LPPALETTEENTRY p_entries);
	MxPalette* Clone();
	void GetDefaultPalette(LPPALETTEENTRY p_entries);
	MxResult GetEntries(LPPALETTEENTRY p_entries);
	MxResult SetEntries(LPPALETTEENTRY p_palette);
	MxResult SetSkyColor(LPPALETTEENTRY p_skyColor);
	void Reset(MxBool p_ignoreSkyColor);
	LPDIRECTDRAWPALETTE CreateNativePalette();

	void SetPalette(LPDIRECTDRAWPALETTE p_palette);

	void SetOverrideSkyColor(MxBool p_value) { m_overrideSkyColor = p_value; }

	// MxPalette::`scalar deleting destructor'

private:
	LPDIRECTDRAWPALETTE m_palette;
	PALETTEENTRY m_entries[256];
	MxBool m_overrideSkyColor;
	PALETTEENTRY m_skyColor;
};

#endif // MXPALETTE_H
