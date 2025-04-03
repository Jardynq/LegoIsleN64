#pragma once

#include "mx_media_manager.h"
#include "mx_video_param.h"

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
	MxDisplaySurface* GetDisplaySurface() { return this->m_displaySurface; }
	MxRegion* GetRegion() { return this->m_region; }

	// MxVideoManager::`scalar deleting destructor'

protected:
	MxVideoParam m_videoParam;
	MxDisplaySurface* m_displaySurface;
	MxRegion* m_region;
	MxBool m_unk0x60;
};

