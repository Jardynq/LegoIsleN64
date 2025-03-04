#ifndef MXVIDEOMANAGER_H
#define MXVIDEOMANAGER_H

#include "mxmediamanager.h"
#include "mxvideoparam.h"

#include <d3d.h>

class MxDisplaySurface;
class MxRect32;
class MxRegion;

class MxVideoManager : public MxMediaManager {
public:
	MxVideoManager();
	~MxVideoManager() override;

	MxResult Tickle() override;
	void Destroy() override;
	virtual MxResult VTable0x28(
		MxVideoParam& p_videoParam,
		LPDIRECTDRAW p_pDirectDraw,
		LPDIRECT3D2 p_pDirect3D,
		LPDIRECTDRAWSURFACE p_ddSurface1,
		LPDIRECTDRAWSURFACE p_ddSurface2,
		LPDIRECTDRAWCLIPPER p_ddClipper,
		MxU32 p_frequencyMS,
		MxBool p_createThread
	);
	virtual MxResult Create(
		MxVideoParam& p_videoParam,
		MxU32 p_frequencyMS,
		MxBool p_createThread
	);

	void InvalidateRect(MxRect32&);
	virtual MxResult RealizePalette(MxPalette*);
	virtual void
	UpdateView(MxU32 p_x, MxU32 p_y, MxU32 p_width, MxU32 p_height);

	MxResult Init();
	void Destroy(MxBool p_fromDestructor);
	void SortPresenterList();
	void UpdateRegion();

	MxVideoParam& GetVideoParam() { return this->m_videoParam; }
	LPDIRECTDRAW GetDirectDraw() { return this->m_pDirectDraw; }
	MxDisplaySurface* GetDisplaySurface() { return this->m_displaySurface; }
	MxRegion* GetRegion() { return this->m_region; }

	// MxVideoManager::`scalar deleting destructor'

protected:
	MxVideoParam m_videoParam;
	LPDIRECTDRAW m_pDirectDraw;
	LPDIRECT3D2 m_pDirect3D;
	MxDisplaySurface* m_displaySurface;
	MxRegion* m_region;
	MxBool m_unk0x60;
};

#endif // MXVIDEOMANAGER_H
