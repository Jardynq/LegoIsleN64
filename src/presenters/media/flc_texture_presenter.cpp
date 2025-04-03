#include "flc_texture_presenter.h"

#include "misc.h"
#include "container.h"
#include "mx_ds_action.h"

LegoFlcTexturePresenter::LegoFlcTexturePresenter() {
	Init();
}

void LegoFlcTexturePresenter::Init() {
	m_rectCount = 0;
	m_texture = NULL;
}

void LegoFlcTexturePresenter::StartingTickle() {
	MxU16 extraLength;
	char* pp;
	char extraCopy[128];
	m_action->GetExtra(extraLength, pp);

	if (pp != NULL) {
		strcpy(extraCopy, pp);
		strcat(extraCopy, ".gif");
		m_texture = TextureContainer()->Get(extraCopy);
	}

	MxFlcPresenter::StartingTickle();
}

void LegoFlcTexturePresenter::LoadFrame(MxStreamChunk* p_chunk) {
	MxU8* data = p_chunk->GetData();

	m_rectCount = *(MxS32*) data;
	data += sizeof(MxS32);

	MxRect32* rects = (MxRect32*) data;
	data += m_rectCount * sizeof(MxRect32);

	MxBool decodedColorMap;
	DecodeFLCFrame(
		&m_frameBitmap->GetBitmapInfo()->m_bmiHeader,
		m_frameBitmap->GetImage(),
		m_flcHeader,
		(FLIC_FRAME*) data,
		&decodedColorMap
	);
}

void LegoFlcTexturePresenter::PutFrame() {
	if (m_texture != NULL && m_rectCount != 0) {
		m_texture->FUN_10066010(m_frameBitmap->GetImage());
		m_rectCount = 0;
	}
}
