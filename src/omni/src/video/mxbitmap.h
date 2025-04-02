#ifndef MXBITMAP_H
#define MXBITMAP_H

#include "mxcore.h"

#include <stdlib.h>

class MxPalette;

// The stock BITMAPINFO struct from wingdi.h only makes room for one color
// in the palette. It seems like the expectation (if you use the struct)
// is to malloc as much as you actually need, and then index into the array
// anyway even though its stated size is [1].
// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfo
// In our case, the size 0x428 is used frequently, which matches
// a 40-byte header plus 256 colors, so just use that as our template.

struct MxBITMAPINFO {
	BITMAPINFOHEADER m_bmiHeader;
	RGBQUAD m_bmiColors[256];

	static MxU32 Size() { return sizeof(MxBITMAPINFO); }
};

// Non-standard value for biCompression in the BITMAPINFOHEADER struct.
// By default, uncompressed bitmaps (BI_RGB) are stored in bottom-up order.
// You can specify that the bitmap has top-down order instead by providing
// a negative number for biHeight. It could be that Mindscape decided on a
// belt & suspenders approach here.
#define BI_RGB_TOPDOWN 0x10

class MxBitmap : public MxCore {
public:
	MxBitmap();
	~MxBitmap() override;

	virtual MxResult ImportBitmap(MxBitmap* p_bitmap);
	virtual MxResult ImportBitmapInfo(MxBITMAPINFO* p_info);
	virtual MxResult
	SetSize(MxS32 p_width, MxS32 p_height, MxPalette* p_palette, MxBool);
	virtual MxResult LoadFile(HANDLE p_handle);
	virtual MxLong Read(const char* p_filename);

	virtual MxS32 VTable0x28(MxS32) { return -1; }

	virtual void BitBlt(
		MxBitmap* p_src,
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_right,
		MxS32 p_bottom,
		MxS32 p_width,
		MxS32 p_height
	);
	virtual void BitBltTransparent(
		MxBitmap* p_src,
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_right,
		MxS32 p_bottom,
		MxS32 p_width,
		MxS32 p_height
	);
	virtual MxPalette* CreatePalette();
	virtual void ImportPalette(MxPalette* p_palette);
	virtual MxResult SetBitDepth(MxBool);
	virtual MxResult StretchBits(
		HDC p_hdc,
		MxS32 p_xSrc,
		MxS32 p_ySrc,
		MxS32 p_xDest,
		MxS32 p_yDest,
		MxS32 p_destWidth,
		MxS32 p_destHeight
	);

	// Bit mask trick to round up to the nearest multiple of four.
	// Pixel data may be stored with padding.
	// https://learn.microsoft.com/en-us/windows/win32/medfound/image-stride

	MxLong AlignToFourByte(MxLong p_value) const { return (p_value + 3) & -4; }

	// DECOMP: This could be a free function. It is static here because it has
	// no reference to "this". In the beta it is called in two places:
	// 1. GetBmiHeightAbs
	// 2. MxSmk::LoadFrame

	static MxLong HeightAbs(MxLong p_value) {
		return p_value > 0 ? p_value : -p_value;
	}

	BITMAPINFOHEADER* GetBmiHeader() const { return m_bmiHeader; }

	MxLong GetBmiWidth() const { return m_bmiHeader->biWidth; }
	MxLong GetBmiStride() const { return ((m_bmiHeader->biWidth + 3) & -4); }
	MxLong GetBmiHeight() const { return m_bmiHeader->biHeight; }

	MxLong GetBmiHeightAbs() const { return HeightAbs(m_bmiHeader->biHeight); }

	MxU8* GetImage() const { return m_data; }

	MxBITMAPINFO* GetBitmapInfo() const { return m_info; }

	MxLong GetDataSize() const {
		return AlignToFourByte(m_bmiHeader->biWidth) * GetBmiHeightAbs();
	}

	MxBool IsTopDown() {
		if (m_bmiHeader->biCompression == BI_RGB_TOPDOWN) {
			return TRUE;
		} else {
			return m_bmiHeader->biHeight < 0;
		}
	}

#define GetAdjustedStride(p_bitmap)                                            \
	((p_bitmap)->IsTopDown()                                                   \
		 ? (p_bitmap)->AlignToFourByte((p_bitmap)->GetBmiWidth())              \
		 : -(p_bitmap)->AlignToFourByte((p_bitmap)->GetBmiWidth()))

	MxU8* GetStart(MxS32 p_left, MxS32 p_top) {
		if (m_bmiHeader->biCompression == BI_RGB) {
			return m_data + p_left +
				   AlignToFourByte(GetBmiWidth()) *
					   (IsTopDown() ? p_top : (GetBmiHeightAbs() - 1) - p_top);
		} else if (m_bmiHeader->biCompression == BI_RGB_TOPDOWN) {
			return m_data;
		} else {
			return m_data + AlignToFourByte(GetBmiWidth()) *
								(IsTopDown() ? 0 : (GetBmiHeightAbs() - 1));
		}
	}

	// MxBitmap::`scalar deleting destructor'

private:
	MxLong MxBitmapInfoSize() const {
		return sizeof(MxBITMAPINFO);
	}

	MxBool IsBottomUp() {
		if (m_bmiHeader->biCompression == BI_RGB_TOPDOWN) {
			return FALSE;
		} else {
			return m_bmiHeader->biHeight > 0;
		}
	}

	MxResult ImportColorsToPalette(RGBQUAD*, MxPalette*);

	MxBITMAPINFO* m_info;
	BITMAPINFOHEADER* m_bmiHeader;
	RGBQUAD* m_paletteData;
	MxU8* m_data;
	MxBool m_isHighColor;
	MxPalette* m_palette;
};

#endif // MXBITMAP_H
