#include "mxdirect3d.h"
#include "mxdebug.h"
#include <stdio.h>


void printDDPixelFormat(const DDPIXELFORMAT* pf) {
	printf("DDPIXELFORMAT:\n");
	printf("  Size:              %u bytes\n", pf->dwSize);
	printf("  Flags:             0x%08X\n", pf->dwFlags);
	printf("  FourCC:            0x%08X ('%c%c%c%c')\n",
		pf->dwFourCC,
		(pf->dwFourCC) & 0xFF,
		(pf->dwFourCC >> 8) & 0xFF,
		(pf->dwFourCC >> 16) & 0xFF,
		(pf->dwFourCC >> 24) & 0xFF);

	printf("  Bit Depths:\n");
	printf("    RGB Bit Count:   %u\n", pf->dwRGBBitCount);
	printf("    YUV Bit Count:   %u\n", pf->dwYUVBitCount);
	printf("    ZBuffer Depth:   %u\n", pf->dwZBufferBitDepth);
	printf("    Alpha Depth:     %u\n", pf->dwAlphaBitDepth);

	printf("  Bit Masks:\n");
	printf("    Red (R) Mask:    0x%08X\n", pf->dwRBitMask);
	printf("    Green (G) Mask:  0x%08X\n", pf->dwGBitMask);
	printf("    Blue (B) Mask:   0x%08X\n", pf->dwBBitMask);
	printf("    Alpha Mask:      0x%08X\n", pf->dwRGBAlphaBitMask);

	printf("\n");
}


void printDDSurfaceDesc(const DDSURFACEDESC* desc) {
	printf("DDSURFACEDESC:\n");
	printf("  Size:                %u bytes\n", desc->dwSize);
	printf("  Flags:               0x%08X\n", desc->dwFlags);
	printf("  Dimensions:          %u x %u\n", desc->dwWidth, desc->dwHeight);

	printf("  Pitch/LinearSize:    %d (0x%08X)\n", desc->lPitch, desc->dwLinearSize);
	printf("  Back Buffer Count:   %u\n", desc->dwBackBufferCount);

	printf("  MipMap Count:        %u\n", desc->dwMipMapCount);
	printf("  Z-Buffer Bit Depth:  %u\n", desc->dwZBufferBitDepth);
	printf("  Refresh Rate:        %u Hz\n", desc->dwRefreshRate);

	printf("  Alpha Bit Depth:     %u\n", desc->dwAlphaBitDepth);
	printf("  Reserved:            0x%08X\n", desc->dwReserved);
	printf("  Surface Pointer:     %p\n", desc->lpSurface);

	printf("  Color Keys:\n");
	printf("    Dest Overlay:      Low: 0x%08X  High: 0x%08X\n",
		desc->ddckCKDestOverlay.dwColorSpaceLowValue, desc->ddckCKDestOverlay.dwColorSpaceHighValue);
	printf("    Dest Blt:          Low: 0x%08X  High: 0x%08X\n",
		desc->ddckCKDestBlt.dwColorSpaceLowValue, desc->ddckCKDestBlt.dwColorSpaceHighValue);
	printf("    Src Overlay:       Low: 0x%08X  High: 0x%08X\n",
		desc->ddckCKSrcOverlay.dwColorSpaceLowValue, desc->ddckCKSrcOverlay.dwColorSpaceHighValue);
	printf("    Src Blt:           Low: 0x%08X  High: 0x%08X\n",
		desc->ddckCKSrcBlt.dwColorSpaceLowValue, desc->ddckCKSrcBlt.dwColorSpaceHighValue);

	printf("  Pixel Format:\n");
	printf("    Size:              %u bytes\n", desc->ddpfPixelFormat.dwSize);
	printf("    Flags:             0x%08X\n", desc->ddpfPixelFormat.dwFlags);
	printf("    FourCC:            0x%08X ('%c%c%c%c')\n",
		desc->ddpfPixelFormat.dwFourCC,
		(desc->ddpfPixelFormat.dwFourCC) & 0xFF,
		(desc->ddpfPixelFormat.dwFourCC >> 8) & 0xFF,
		(desc->ddpfPixelFormat.dwFourCC >> 16) & 0xFF,
		(desc->ddpfPixelFormat.dwFourCC >> 24) & 0xFF);
	printf("    Bit Depth:         %u\n", desc->ddpfPixelFormat.dwRGBBitCount);

	printf("    Red Mask:          0x%08X\n", desc->ddpfPixelFormat.dwRBitMask);
	printf("    Green Mask:        0x%08X\n", desc->ddpfPixelFormat.dwGBitMask);
	printf("    Blue Mask:         0x%08X\n", desc->ddpfPixelFormat.dwBBitMask);
	printf("    Alpha Mask:        0x%08X\n", desc->ddpfPixelFormat.dwRGBAlphaBitMask);

	printf("  Surface Capabilities:\n");
	printf("    Caps:              0x%08X\n", desc->ddsCaps.dwCaps);

	printf("\n");
}

void printDDSCaps(DWORD dwCaps) {
	printf("  Surface Capabilities (ddsCaps.dwCaps):\n");

	if (dwCaps & 0x00000001) printf("    - DDSCAPS_ALPHA: Surface contains alpha channel\n");
	if (dwCaps & 0x00000002) printf("    - DDSCAPS_BACKBUFFER: Surface is a back buffer\n");
	if (dwCaps & 0x00000004) printf("    - DDSCAPS_COMPLEX: Surface is complex (e.g., mipmaps)\n");
	if (dwCaps & 0x00000008) printf("    - DDSCAPS_FLIP: Surface supports flipping\n");
	if (dwCaps & 0x00000010) printf("    - DDSCAPS_FRONTBUFFER: Surface is a front buffer\n");
	if (dwCaps & 0x00000020) printf("    - DDSCAPS_OFFSCREENPLAIN: Offscreen surface\n");
	if (dwCaps & 0x00000040) printf("    - DDSCAPS_OVERLAY: Surface is an overlay\n");
	if (dwCaps & 0x00000080) printf("    - DDSCAPS_PALETTE: Surface has an attached palette\n");
	if (dwCaps & 0x00000100) printf("    - DDSCAPS_PRIMARYSURFACE: Surface is the primary display\n");
	if (dwCaps & 0x00000200) printf("    - DDSCAPS_SYSTEMMEMORY: Surface is stored in system memory\n");
	if (dwCaps & 0x00000400) printf("    - DDSCAPS_TEXTURE: Surface is used as a texture\n");
	if (dwCaps & 0x00000800) printf("    - DDSCAPS_VIDEOMEMORY: Surface is stored in video memory\n");
	if (dwCaps & 0x00001000) printf("    - DDSCAPS_WRITEONLY: Surface is write-only\n");
	if (dwCaps & 0x00002000) printf("    - DDSCAPS_ZBUFFER: Surface is a Z-buffer\n");
	if (dwCaps & 0x00004000) printf("    - DDSCAPS_OWNDC: Surface has its own device context (DC)\n");
	if (dwCaps & 0x00008000) printf("    - DDSCAPS_LIVEVIDEO: Surface is receiving live video\n");
	if (dwCaps & 0x00010000) printf("    - DDSCAPS_HWCODEC: Hardware-accelerated codec surface\n");
	if (dwCaps & 0x00020000) printf("    - DDSCAPS_MODEX: ModeX surface\n");
	if (dwCaps & 0x00040000) printf("    - DDSCAPS_MIPMAP: Surface is one level of a mipmap chain\n");
	if (dwCaps & 0x00080000) printf("    - DDSCAPS_RESERVED2\n");
	if (dwCaps & 0x00100000) printf("    - DDSCAPS_ALLOCONLOAD: Allocated when loaded\n");
	if (dwCaps & 0x00200000) printf("    - DDSCAPS_VIDEOPORT: Surface is part of a video port\n");
	if (dwCaps & 0x00400000) printf("    - DDSCAPS_LOCALVIDMEM: Surface is in local video memory\n");
	if (dwCaps & 0x00800000) printf("    - DDSCAPS_NONLOCALVIDMEM: Surface is in non-local video memory\n");
	if (dwCaps & 0x01000000) printf("    - DDSCAPS_STANDARDVGAMODE: Supports standard VGA mode\n");
	if (dwCaps & 0x02000000) printf("    - DDSCAPS_OPTIMIZED: Optimized surface\n");
	if (dwCaps & 0x04000000) printf("    - DDSCAPS2_HARDWAREDEINTERLACE: Supports hardware deinterlacing\n");
	if (dwCaps == 0) printf("    - (No specific capabilities set)\n");
}

void printDDCaps(const DDCAPS* caps, const char* label) {
	printf("\n--- %s ---\n", label);
	printf("  Size:                  %u bytes\n", caps->dwSize);
	printf("  Max Surface Width:     %u\n", caps->dwMaxVisibleOverlays);
	printf("  Max Overlay Stretch:   %u%%\n", caps->dwMinOverlayStretch);
	printf("  Max Video Memory:      %u KB\n", caps->dwVidMemTotal / 1024);
	printf("  Free Video Memory:     %u KB\n", caps->dwVidMemFree / 1024);

	printf("\n  Hardware Capabilities:\n");
	if (caps->dwCaps & DDCAPS_3D)               printf("    - Supports 3D acceleration\n");
	if (caps->dwCaps & DDCAPS_BLT)              printf("    - Supports BLT (Bit Block Transfer)\n");
	if (caps->dwCaps & DDCAPS_BLTQUEUE)         printf("    - Supports queued BLTs\n");
	if (caps->dwCaps & DDCAPS_BLTCOLORFILL)     printf("    - Supports color fill BLTs\n");
	if (caps->dwCaps & DDCAPS_GDI)              printf("    - Can render with GDI\n");
	if (caps->dwCaps & DDCAPS_OVERLAY)          printf("    - Supports hardware overlay\n");
	if (caps->dwCaps & DDCAPS_OVERLAYCANTCLIP)  printf("    - Cannot clip overlays\n");
	if (caps->dwCaps & DDCAPS_OVERLAYSTRETCH)   printf("    - Supports overlay stretching\n");
	if (caps->dwCaps & DDCAPS_ALPHA)            printf("    - Supports alpha blending\n");
	if (caps->dwCaps & DDCAPS_COLORKEY)         printf("    - Supports colorkeying\n");
	if (caps->dwCaps & DDCAPS_CANCLIP)          printf("    - Supports surface clipping\n");
	if (caps->dwCaps & DDCAPS_CANBLTSYSMEM)     printf("    - Can BLT from system memory\n");
	if (caps->dwCaps & DDCAPS_READSCANLINE)     printf("    - Can read the current scanline\n");

	printf("\n  Memory Alignment:\n");
	printf("    - Align Boundary:   %u bytes\n", caps->dwAlignBoundarySrc);
	printf("    - Align Size Src:   %u bytes\n", caps->dwAlignSizeSrc);
	printf("    - Align Boundary Dest: %u bytes\n", caps->dwAlignBoundaryDest);
	printf("    - Align Size Dest:  %u bytes\n", caps->dwAlignSizeDest);

	printf("\n  Overlay Capabilities:\n");
	if (caps->dwCaps2 & DDCAPS2_CANBOBINTERLEAVED) printf("    - Supports interleaved bob deinterlacing\n");
	if (caps->dwCaps2 & DDCAPS2_CANBOBNONINTERLEAVED) printf("    - Supports non-interleaved bob deinterlacing\n");
	if (caps->dwCaps2 & DDCAPS2_WIDESURFACES) printf("    - Supports wide surfaces\n");

	printf("\n");
}


#if !defined(MXDIRECTX_FOR_CONFIG)
#define RELEASE(x)                                                                                                     \
	if (x != NULL) {                                                                                                   \
		x->Release();                                                                                                  \
		x = NULL;                                                                                                      \
	}

// FUNCTION: LEGO1 0x1009b0a0
MxDirect3D::MxDirect3D() {
	this->m_pDirect3d = NULL;
	this->m_pDirect3dDevice = NULL;
	this->m_bTexturesDisabled = FALSE;
	this->m_assignedDevice = NULL;
}

// FUNCTION: LEGO1 0x1009b140
MxDirect3D::~MxDirect3D() {
	Destroy();
}

// FUNCTION: LEGO1 0x1009b1a0
BOOL MxDirect3D::Create(
	HWND hWnd,
	BOOL fullscreen_1,
	BOOL surface_fullscreen,
	BOOL onlySystemMemory,
	int width,
	int height,
	int bpp,
	const PALETTEENTRY* pPaletteEntries,
	int paletteEntryCount
) {
	BOOL success = TRUE;
	BOOL ret = MxDirectDraw::Create(
		hWnd,
		fullscreen_1,
		surface_fullscreen,
		onlySystemMemory,
		width,
		height,
		bpp,
		pPaletteEntries,
		paletteEntryCount
	);
	if (!ret) {
		success = FALSE;
		printf("Failed to create mx direct draw\n");
	}
	if (!D3DCreate()) {
		success = FALSE;
		printf("Failed to create mx direct 3d\n");
	}
	if (!D3DSetMode()) {
		success = FALSE;
		printf("Failed to set mx direct 3d mode\n");
	}

	if (!success) {
		FUN_1009d920();
	}

	return success;
}

// FUNCTION: LEGO1 0x1009b210
void MxDirect3D::Destroy() {
	RELEASE(m_pDirect3dDevice);
	RELEASE(m_pDirect3d);

	if (this->m_assignedDevice) {
		delete m_assignedDevice;
		this->m_assignedDevice = NULL;
	}

	if (m_pCurrentDeviceModesList) {
		m_pCurrentDeviceModesList = NULL;
	}

	MxDirectDraw::Destroy();
}

// FUNCTION: LEGO1 0x1009b290
void MxDirect3D::DestroyButNotDirectDraw() {
	RELEASE(m_pDirect3dDevice);
	RELEASE(m_pDirect3d);
	MxDirectDraw::DestroyButNotDirectDraw();
}

// FUNCTION: LEGO1 0x1009b2d0
BOOL MxDirect3D::D3DCreate() {
	HRESULT result;

	result = DirectDraw()->QueryInterface(IID_IDirect3D2, (LPVOID*)&m_pDirect3d);
	if (result != DD_OK) {
		Error("Creation of IDirect3D failed", result);
		return FALSE;
	}
	return TRUE;
}

// FUNCTION: LEGO1 0x1009b310
BOOL MxDirect3D::D3DSetMode() {
	if (m_assignedDevice->m_flags & MxAssignedDevice::c_hardwareMode) {
		printf("Using hardware renderer\n");
		if (m_bOnlySoftRender) {
			Error("Failed to place vital surfaces in video memory for hardware driver", DDERR_GENERIC);
			return FALSE;
		}

		if (m_assignedDevice->m_desc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE) {
			m_bTexturesDisabled = FALSE;
		}
		else {
			m_bTexturesDisabled = TRUE;
		}

		if (!CreateZBuffer(DDSCAPS_VIDEOMEMORY, ZBufferDepth(m_assignedDevice))) {
			return FALSE;
		}
	}
	else {
		printf("Using software renderer\n");
		if (m_assignedDevice->m_desc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE) {
			m_bTexturesDisabled = FALSE;
		}
		else {
			m_bTexturesDisabled = TRUE;
		}

		if (!CreateZBuffer(DDSCAPS_SYSTEMMEMORY, ZBufferDepth(m_assignedDevice))) {
			return FALSE;
		}
	}

	DDSCAPS caps;
	DDCAPS capsa;
	DDCAPS capsb;
	DDPIXELFORMAT pixfmt;
	DDSURFACEDESC sdesc;
	DDSURFACEDESC sdesc2;
	HDC hdc;
	if (DD_OK != m_pBackBuffer->GetCaps(&caps)) {
		printf("Failed to get caps\n");
	}
	else {
		printDDSCaps(caps.dwCaps);
	}
	if (DD_OK != m_pBackBuffer->GetPixelFormat(&pixfmt)) {
		printf("Failed to get pixel format\n");
	}
	else {
		printDDPixelFormat(&pixfmt);
	}
	if (DD_OK != m_pBackBuffer->GetSurfaceDesc(&sdesc)) {
		printf("Failed to get surface descriptor\n");
	}
	else {
		printDDSurfaceDesc(&sdesc);
	}
	if (DD_OK != m_pDirectDraw->GetCaps(&capsa, &capsb)) {
		printf("Failed to get d3d caps\n");
	}
	else {
		printDDCaps(&capsa, "First caps");
		printDDCaps(&capsb, "Second caps");
	}
	if (DD_OK != m_pDirectDraw->GetDisplayMode(&sdesc2)) {
		printf("Failed to get d3d surface descriptor\n");
	}
	else {
		printDDSurfaceDesc(&sdesc);
	}


	HRESULT result = m_pDirect3d->CreateDevice(m_assignedDevice->m_guid, m_pBackBuffer, &m_pDirect3dDevice);
	if (result != DD_OK) {
		Error("Create D3D device failed", result);
		return FALSE;
	}

	DeviceModesInfo::Mode mode = m_currentMode;

	if (IsFullScreen()) {
		if (!IsSupportedMode(mode.width, mode.height, mode.bitsPerPixel)) {
			Error("This device cannot support the current display mode", DDERR_GENERIC);
			return FALSE;
		}
	}

	LPDIRECTDRAWSURFACE frontBuffer = m_pFrontBuffer;
	LPDIRECTDRAWSURFACE backBuffer = m_pBackBuffer;

	DDSURFACEDESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);

	if (backBuffer->Lock(NULL, &desc, DDLOCK_WAIT, NULL) == DD_OK) {
		unsigned char* surface = (unsigned char*)desc.lpSurface;

		for (int i = mode.height; i > 0; i--) {
			memset(surface, 0, mode.width * desc.ddpfPixelFormat.dwRGBBitCount / 8);
			surface += desc.lPitch;
		}

		backBuffer->Unlock(desc.lpSurface);
	}
	else {
		_MxTrace("MxDirect3D::D3DSetMode() back lock failed\n");
	}

	if (m_bFullScreen) {
		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);

		if (frontBuffer->Lock(NULL, &desc, DDLOCK_WAIT, NULL) == DD_OK) {
			unsigned char* surface = (unsigned char*)desc.lpSurface;

			for (int i = mode.height; i > 0; i--) {
				memset(surface, 0, mode.width * desc.ddpfPixelFormat.dwRGBBitCount / 8);
				surface += desc.lPitch;
			}

			frontBuffer->Unlock(desc.lpSurface);
		}
		else {
			_MxTrace("MxDirect3D::D3DSetMode() front lock failed\n");
		}
	}

	return TRUE;
}

// FUNCTION: LEGO1 0x1009b5a0
int MxDirect3D::ZBufferDepth(MxAssignedDevice* p_assignedDevice) {
	int depth;
	DWORD deviceDepth;

	if (p_assignedDevice->m_desc.dwFlags & D3DDD_DEVICEZBUFFERBITDEPTH) {
		deviceDepth = p_assignedDevice->m_desc.dwDeviceZBufferBitDepth;
	}
	else {
		deviceDepth = 0;
	}

	if (deviceDepth & DDBD_32) {
		depth = 32;
	}
	else if (deviceDepth & DDBD_24) {
		depth = 24;
	}
	else if (deviceDepth & DDBD_16) {
		depth = 16;
	}
	else if (deviceDepth & DDBD_8) {
		depth = 8;
	}
	else {
		depth = -1;
	}

	return depth;
}

// FUNCTION: LEGO1 0x1009b5f0
// FUNCTION: BETA10 0x1011bbca
BOOL MxDirect3D::SetDevice(MxDeviceEnumerate& p_deviceEnumerate, MxDriver* p_driver, Direct3DDeviceInfo* p_device) {
	if (m_assignedDevice) {
		delete m_assignedDevice;
		m_assignedDevice = NULL;
		m_pCurrentDeviceModesList = NULL;
	}
	printf("%s\n", p_device->m_deviceName);
	printf("%s\n", p_device->m_deviceDesc);

	MxAssignedDevice* assignedDevice = new MxAssignedDevice;
	int i = 0;

	for (list<MxDriver>::iterator it = p_deviceEnumerate.m_list.begin(); it != p_deviceEnumerate.m_list.end(); it++) {
		MxDriver& driver = *it;

		if (&driver == p_driver) {
			assignedDevice->m_deviceInfo = new DeviceModesInfo;

			if (driver.m_guid) {
				assignedDevice->m_deviceInfo->m_guid = new GUID;
				memcpy(assignedDevice->m_deviceInfo->m_guid, driver.m_guid, sizeof(GUID));
			}

			assignedDevice->m_deviceInfo->m_count = driver.m_displayModes.size();

			if (assignedDevice->m_deviceInfo->m_count > 0) {
				assignedDevice->m_deviceInfo->m_modeArray =
					new DeviceModesInfo::Mode[assignedDevice->m_deviceInfo->m_count];

				int j = 0;
				for (list<MxDisplayMode>::iterator it2 = driver.m_displayModes.begin();
					it2 != driver.m_displayModes.end();
					it2++) {
					assignedDevice->m_deviceInfo->m_modeArray[j].width = (*it2).m_width;
					assignedDevice->m_deviceInfo->m_modeArray[j].height = (*it2).m_height;
					assignedDevice->m_deviceInfo->m_modeArray[j].bitsPerPixel = (*it2).m_bitsPerPixel;
					j++;
				}
			}

			memcpy(
				&assignedDevice->m_deviceInfo->m_ddcaps,
				&driver.m_ddCaps,
				sizeof(assignedDevice->m_deviceInfo->m_ddcaps)
			);

			if (i == 0) {
				assignedDevice->m_flags |= MxAssignedDevice::c_primaryDevice;
			}

			for (list<Direct3DDeviceInfo>::iterator it2 = driver.m_devices.begin(); it2 != driver.m_devices.end();
				it2++) {
				Direct3DDeviceInfo& device = *it2;
				if (&device != p_device) {
					continue;
				}

				memcpy(&assignedDevice->m_guid, device.m_guid, sizeof(assignedDevice->m_guid));

				D3DDEVICEDESC* desc;
				if (device.m_HWDesc.dcmColorModel) {
					assignedDevice->m_flags |= MxAssignedDevice::c_hardwareMode;
					desc = &device.m_HWDesc;
				}
				else {
					desc = &device.m_HELDesc;
				}

				memcpy(&assignedDevice->m_desc, desc, sizeof(assignedDevice->m_desc));
				m_assignedDevice = assignedDevice;
				m_pCurrentDeviceModesList = assignedDevice->m_deviceInfo;
				break;
			}
		}

		i++;
	}

	if (!m_assignedDevice) {
		delete assignedDevice;
		return FALSE;
	}

	return TRUE;
}

#endif
