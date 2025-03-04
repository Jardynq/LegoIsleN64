#include "mxflcpresenter.h"

#include "mxbitmap.h"
#include "mxdsmediaaction.h"
#include "mxmisc.h"
#include "mxpalette.h"
#include "mxvideomanager.h"

MxFlcPresenter::MxFlcPresenter() {
	m_flcHeader = NULL;
	SetBit1(FALSE);
	SetBit2(FALSE);
}

MxFlcPresenter::~MxFlcPresenter() {
	if (this->m_flcHeader) {
		delete this->m_flcHeader;
	}
}

void MxFlcPresenter::LoadHeader(MxStreamChunk* p_chunk) {
	m_flcHeader = (FLIC_HEADER*) new MxU8[p_chunk->GetLength()];
	memcpy(m_flcHeader, p_chunk->GetData(), p_chunk->GetLength());
}

void MxFlcPresenter::CreateBitmap() {
	if (m_frameBitmap) {
		delete m_frameBitmap;
	}

	m_frameBitmap = new MxBitmap;
	m_frameBitmap
		->SetSize(m_flcHeader->width, m_flcHeader->height, NULL, FALSE);
}

void MxFlcPresenter::LoadFrame(MxStreamChunk* p_chunk) {
	MxU8* data = p_chunk->GetData();

	MxS32 rectCount = *(MxS32*) data;
	data += sizeof(MxS32);

	MxRect32* rects = (MxRect32*) data;
	data += rectCount * sizeof(MxRect32);

	MxBool decodedColorMap;
	DecodeFLCFrame(
		&m_frameBitmap->GetBitmapInfo()->m_bmiHeader,
		m_frameBitmap->GetImage(),
		m_flcHeader,
		(FLIC_FRAME*) data,
		&decodedColorMap
	);

	if (((MxDSMediaAction*) m_action)->GetPaletteManagement() &&
		decodedColorMap) {
		RealizePalette();
	}

	for (MxS32 i = 0; i < rectCount; i++) {
		MxRect32 rect(rects[i]);
		rect.AddPoint(m_location);
		MVideoManager()->InvalidateRect(rect);
	}
}

void MxFlcPresenter::RealizePalette() {
	MxPalette* palette = m_frameBitmap->CreatePalette();
	MVideoManager()->RealizePalette(palette);
	delete palette;
}
