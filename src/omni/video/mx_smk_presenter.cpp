#include "mx_smk_presenter.h"

#include "mx_ds_media_action.h"
#include "mx_misc.h"
#include "mxpalette.h"
#include "mx_video_manager.h"

MxSmkPresenter::MxSmkPresenter() {
	Init();
}

MxSmkPresenter::~MxSmkPresenter() {
	Destroy(TRUE);
}

void MxSmkPresenter::Init() {
	m_currentFrame = 0;
	memset(&m_mxSmk, 0, sizeof(m_mxSmk));
	SetBit1(FALSE);
	SetBit2(FALSE);
}

void MxSmkPresenter::Destroy(MxBool p_fromDestructor) {
	m_criticalSection.Enter();

	MxSmk::Destroy(&m_mxSmk);
	Init();

	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		MxVideoPresenter::Destroy(FALSE);
	}
}

void MxSmkPresenter::LoadHeader(MxStreamChunk* p_chunk) {
	MxSmk::LoadHeader(p_chunk->GetData(), &m_mxSmk);
}

void MxSmkPresenter::CreateBitmap() {
	if (m_frameBitmap) {
		delete m_frameBitmap;
	}

	m_frameBitmap = new MxBitmap;
	m_frameBitmap->SetSize(
		m_mxSmk.m_smackTag.Width,
		m_mxSmk.m_smackTag.Height,
		NULL,
		FALSE
	);
}

void MxSmkPresenter::LoadFrame(MxStreamChunk* p_chunk) {
	MxBITMAPINFO* bitmapInfo = m_frameBitmap->GetBitmapInfo();
	MxU8* bitmapData = m_frameBitmap->GetImage();
	MxU8* chunkData = p_chunk->GetData();

	MxBool paletteChanged = m_mxSmk.m_frameTypes[m_currentFrame] & 1;
	m_currentFrame++;
	VTable0x88();

	MxRectList rects(TRUE);
	MxSmk::LoadFrame(
		bitmapInfo,
		bitmapData,
		&m_mxSmk,
		chunkData,
		paletteChanged,
		&rects
	);

	if (((MxDSMediaAction*) m_action)->GetPaletteManagement() &&
		paletteChanged) {
		RealizePalette();
	}

	MxRect32 invalidateRect;
	MxRectListCursor cursor(&rects);
	MxRect32* rect;

	while (cursor.Next(rect)) {
		invalidateRect = *rect;
		invalidateRect.AddPoint(GetLocation());
		MVideoManager()->InvalidateRect(invalidateRect);
	}
}

void MxSmkPresenter::VTable0x88() {
	if ((m_mxSmk.m_smackTag.SmackerType & 1) != 0) {
		MxU32 und = (m_currentFrame % m_mxSmk.m_smackTag.Frames);
		if (1 < m_currentFrame && und == 1) {
			m_currentFrame = 1;
		}
	} else {
		if (m_mxSmk.m_smackTag.Frames == m_currentFrame) {
			m_currentFrame = 0;
			// TODO: struct incorrect, Palette at wrong offset?
			memset(
				&m_mxSmk.m_smackTag.Palette[4],
				0,
				sizeof(m_mxSmk.m_smackTag.Palette)
			);
		}
	}
}

void MxSmkPresenter::RealizePalette() {
	MxPalette* palette = m_frameBitmap->CreatePalette();
	MVideoManager()->RealizePalette(palette);
	delete palette;
}

MxResult MxSmkPresenter::AddToManager() {
	return MxVideoPresenter::AddToManager();
}

void MxSmkPresenter::Destroy() {
	Destroy(FALSE);
}
