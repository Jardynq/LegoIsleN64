#ifndef MXVIDEOPARAM_H
#define MXVIDEOPARAM_H

#include "mxrect32.h"
#include "mxvideoparamflags.h"

class MxPalette;

class MxVideoParam {
public:
	MxVideoParam();
	MxVideoParam(
		MxRect32& p_rect,
		MxPalette* p_palette,
		MxULong p_backBuffers,
		MxVideoParamFlags& p_flags
	);
	MxVideoParam(MxVideoParam& p_videoParam);
	~MxVideoParam();
	void SetDeviceName(char* p_deviceId);
	MxVideoParam& operator=(const MxVideoParam& p_videoParam);

	MxVideoParamFlags& Flags() { return m_flags; }

	MxRect32& GetRect() { return m_rect; }

	MxPalette* GetPalette() { return m_palette; }

	void SetPalette(MxPalette* p_palette) { m_palette = p_palette; }

	char* GetDeviceName() { return m_deviceId; }

	MxU32 GetBackBuffers() { return m_backBuffers; }

	void SetBackBuffers(MxU32 p_backBuffers) { m_backBuffers = p_backBuffers; }

private:
	MxRect32 m_rect;
	MxPalette* m_palette;
	MxU32 m_backBuffers;
	MxVideoParamFlags m_flags;
	int m_unk0x1c;
	char* m_deviceId;
};

#endif // MXVIDEOPARAM_H
