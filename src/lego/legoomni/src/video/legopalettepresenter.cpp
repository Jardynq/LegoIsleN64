#include "legopalettepresenter.h"

#include "legovideomanager.h"
#include "misc.h"
#include "misc/legostorage.h"
#include "mxdsaction.h"
#include "mxdssubscriber.h"
#include "mxpalette.h"
#include "mxstreamchunk.h"

LegoPalettePresenter::LegoPalettePresenter() {
	Init();
}

LegoPalettePresenter::~LegoPalettePresenter() {
	Destroy(TRUE);
}

void LegoPalettePresenter::Init() {
	m_palette = NULL;
}

void LegoPalettePresenter::Destroy(MxBool p_fromDestructor) {
	m_criticalSection.Enter();
	if (m_palette) {
		delete m_palette;
	}
	Init();
	m_criticalSection.Leave();
	if (!p_fromDestructor) {
		MxVideoPresenter::Destroy(FALSE);
	}
}

void LegoPalettePresenter::Destroy() {
	Destroy(FALSE);
}

MxResult LegoPalettePresenter::ParsePalette(MxStreamChunk* p_chunk) {
	MxU8 buffer[40];
	RGBQUAD palette[256];
	MxResult result = FAILURE;

	LegoMemory stream((char*) p_chunk->GetData());
	if (stream.Read(buffer, sizeof(buffer)) == SUCCESS) {
		if (stream.Read(palette, sizeof(palette)) == SUCCESS) {
			m_palette = new MxPalette(palette);
			if (m_palette) {
				result = SUCCESS;
			}
		}
	}

	if (result != SUCCESS && m_palette) {
		delete m_palette;
		m_palette = NULL;
	}

	return result;
}

void LegoPalettePresenter::ReadyTickle() {
	MxStreamChunk* chunk = m_subscriber->PeekData();
	if (chunk) {
		if (chunk->GetTime() <= m_action->GetElapsedTime()) {
			ParseExtra();
			ProgressTickleState(e_starting);

			chunk = m_subscriber->PopData();
			MxResult result = ParsePalette(chunk);
			m_subscriber->FreeDataChunk(chunk);

			if (result == SUCCESS) {
				VideoManager()->RealizePalette(m_palette);
			}
			EndAction();
		}
	}
}
