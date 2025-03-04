#include "mxvideomanager.h"

#include "mxautolock.h"
#include "mxdisplaysurface.h"
#include "mxmisc.h"
#include "mxomni.h"
#include "mxpalette.h"
#include "mxpresenter.h"
#include "mxregion.h"
#include "mxticklemanager.h"
#include "mxticklethread.h"
#include "stdio.h"

MxVideoManager::MxVideoManager() {
	Init();
}

void MxVideoManager::UpdateView(
	MxU32 p_x,
	MxU32 p_y,
	MxU32 p_width,
	MxU32 p_height
) {
}

MxVideoManager::~MxVideoManager() {
	Destroy(TRUE);
}

MxResult MxVideoManager::Init() {
	this->m_pDirectDraw = NULL;
	this->m_pDirect3D = NULL;
	this->m_displaySurface = NULL;
	this->m_region = NULL;
	this->m_videoParam.SetPalette(NULL);
	this->m_unk0x60 = FALSE;
	return SUCCESS;
}

void MxVideoManager::Destroy(MxBool p_fromDestructor) {
	if (m_thread) {
		m_thread->Terminate();
		delete m_thread;
	} else {
		TickleManager()->UnregisterClient(this);
	}

	m_criticalSection.Enter();

	if (m_displaySurface) {
		delete m_displaySurface;
	}

	if (m_region) {
		delete m_region;
	}

	if (m_videoParam.GetPalette()) {
		delete m_videoParam.GetPalette();
	}

	if (m_unk0x60) {
		if (m_pDirectDraw) {
			m_pDirectDraw->Release();
		}
		if (m_pDirect3D) {
			m_pDirect3D->Release();
		}
	}

	Init();
	m_criticalSection.Leave();

	if (!p_fromDestructor) {
		MxMediaManager::Destroy();
	}
}

void MxVideoManager::UpdateRegion() {
	if (m_region->VTable0x20() == FALSE) {
		MxRect32 rect(m_region->GetRect());
		rect.Intersect(m_videoParam.GetRect());

		m_displaySurface->Display(
			rect.GetLeft(),
			rect.GetTop(),
			rect.GetLeft(),
			rect.GetTop(),
			rect.GetWidth(),
			rect.GetHeight()
		);
	}
}

void MxVideoManager::SortPresenterList() {
	if (this->m_presenters->GetCount() <= 1) {
		return;
	}

	MxPresenterListCursor a(this->m_presenters);
	MxPresenterListCursor b(this->m_presenters);
	MxU32 count = this->m_presenters->GetCount() - 1;
	MxBool finished;

	if (count != 0) {
		do {
			a.Reset();
			b.Head();

			finished = TRUE;
			for (MxU32 i = count; i != 0; i--) {
				MxPresenter *presenterA, *presenterB;

				a.Next(presenterA);
				b.Next(presenterB);

				if (presenterA->GetDisplayZ() < presenterB->GetDisplayZ()) {
					a.SetValue(presenterB);
					b.SetValue(presenterA);
					finished = FALSE;
				}
			}
		} while (!finished && --count != 0);
	}
}

MxResult MxVideoManager::VTable0x28(
	MxVideoParam& p_videoParam,
	LPDIRECTDRAW p_pDirectDraw,
	LPDIRECT3D2 p_pDirect3D,
	LPDIRECTDRAWSURFACE p_ddSurface1,
	LPDIRECTDRAWSURFACE p_ddSurface2,
	LPDIRECTDRAWCLIPPER p_ddClipper,
	MxU32 p_frequencyMS,
	MxBool p_createThread
) {
	MxBool locked = FALSE;
	MxResult status = FAILURE;

	m_unk0x60 = FALSE;

	if (MxMediaManager::Create() != SUCCESS) {
		goto done;
	}

	m_criticalSection.Enter();
	locked = TRUE;

	m_videoParam = p_videoParam;
	m_region = new MxRegion();

	if (!m_region) {
		goto done;
	}

	m_pDirectDraw = p_pDirectDraw;
	m_pDirect3D = p_pDirect3D;

	MxPalette* palette;
	if (p_videoParam.GetPalette() == NULL) {
		palette = new MxPalette();
		m_videoParam.SetPalette(palette);

		if (!palette) {
			goto done;
		}
	} else {
		palette = p_videoParam.GetPalette()->Clone();
		m_videoParam.SetPalette(palette);

		if (!palette) {
			goto done;
		}
	}

	m_displaySurface = new MxDisplaySurface();
	if (m_displaySurface &&
		m_displaySurface
				->Init(m_videoParam, p_ddSurface1, p_ddSurface2, p_ddClipper) ==
			SUCCESS) {
		m_displaySurface->SetPalette(m_videoParam.GetPalette());

		if (p_createThread) {
			m_thread = new MxTickleThread(this, p_frequencyMS);

			if (!m_thread || m_thread->Start(0, 0) != SUCCESS) {
				goto done;
			}
		} else {
			TickleManager()->RegisterClient(this, p_frequencyMS);
		}

		status = SUCCESS;
	}

done:
	if (status != SUCCESS) {
		Destroy();
	}

	if (locked) {
		m_criticalSection.Leave();
	}

	return status;
}

MxResult MxVideoManager::Create(
	MxVideoParam& p_videoParam,
	MxU32 p_frequencyMS,
	MxBool p_createThread
) {
	MxBool locked = FALSE;
	MxResult status = FAILURE;

	m_unk0x60 = TRUE;

	if (MxMediaManager::Create() != SUCCESS) {
		printf("Failed to create MX media manager\n");
		goto done;
	}

	m_criticalSection.Enter();
	locked = TRUE;

	m_videoParam = p_videoParam;
	m_region = new MxRegion();

	if (!m_region) {
		printf("Failed to create MX region\n");
		goto done;
	}

	if (DirectDrawCreate(NULL, &m_pDirectDraw, NULL) != DD_OK) {
		printf("Failed to create direct draw\n");
		goto done;
	}

	if (m_pDirectDraw->SetCooperativeLevel(
			MxOmni::GetInstance()->GetWindowHandle(),
			DDSCL_NORMAL
		) != DD_OK) {
		printf("Failed to set direct draw cooperative level\n");
		goto done;
	}

	MxPalette* palette;
	if (p_videoParam.GetPalette() == NULL) {
		palette = new MxPalette();
		m_videoParam.SetPalette(palette);

		if (!palette) {
			printf("Failed to set palette\n");
			goto done;
		}
	} else {
		palette = p_videoParam.GetPalette()->Clone();
		m_videoParam.SetPalette(palette);

		if (!palette) {
			printf("Failed to set palette\n");
			goto done;
		}
	}

	m_displaySurface = new MxDisplaySurface();
	if (m_displaySurface && m_displaySurface->Create(m_videoParam) == SUCCESS) {
		m_displaySurface->SetPalette(m_videoParam.GetPalette());

		if (p_createThread) {
			m_thread = new MxTickleThread(this, p_frequencyMS);

			if (!m_thread || m_thread->Start(0, 0) != SUCCESS) {
				printf("Failed to start tickle thread\n");
				goto done;
			}
		} else {
			TickleManager()->RegisterClient(this, p_frequencyMS);
		}

		status = SUCCESS;
	}

done:
	if (status != SUCCESS) {
		Destroy();
	}

	if (locked) {
		m_criticalSection.Leave();
	}

	return status;
}

void MxVideoManager::Destroy() {
	Destroy(FALSE);
}

void MxVideoManager::InvalidateRect(MxRect32& p_rect) {
	m_criticalSection.Enter();

	if (m_region) {
		m_region->VTable0x18(p_rect);
	}

	m_criticalSection.Leave();
}

MxResult MxVideoManager::Tickle() {
	AUTOLOCK(m_criticalSection);

	SortPresenterList();

	MxPresenter* presenter;
	MxPresenterListCursor cursor(this->m_presenters);

	while (cursor.Next(presenter)) {
		presenter->Tickle();
	}

	cursor.Reset();

	while (cursor.Next(presenter)) {
		presenter->PutData();
	}

	UpdateRegion();
	m_region->Reset();

	return SUCCESS;
}

MxResult MxVideoManager::RealizePalette(MxPalette* p_palette) {
	PALETTEENTRY paletteEntries[256];

	this->m_criticalSection.Enter();

	if (p_palette && this->m_videoParam.GetPalette()) {
		p_palette->GetEntries(paletteEntries);
		this->m_videoParam.GetPalette()->SetEntries(paletteEntries);
		this->m_displaySurface->SetPalette(this->m_videoParam.GetPalette());
	}

	this->m_criticalSection.Leave();
	return SUCCESS;
}
