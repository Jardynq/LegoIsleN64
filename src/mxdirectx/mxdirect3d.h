#ifndef MXDIRECT3D_H
#define MXDIRECT3D_H

#include "mxdirectdraw.h"
#include "mxdirectxinfo.h"

#include <d3d.h>

class MxDirect3D : public MxDirectDraw {
public:
	MxDirect3D();
	~MxDirect3D() override;

	BOOL Create(
		HWND hWnd,
		BOOL fullscreen_1,
		BOOL surface_fullscreen,
		BOOL onlySystemMemory,
		int width,
		int height,
		int bpp,
		const PALETTEENTRY* pPaletteEntries,
		int paletteEntryCount
	) override;
	void Destroy() override;
	void DestroyButNotDirectDraw() override;

	MxAssignedDevice* AssignedDevice() { return this->m_assignedDevice; }
	IDirect3D2* Direct3D() { return this->m_pDirect3d; }
	IDirect3DDevice2* Direct3DDevice() { return this->m_pDirect3dDevice; }

	BOOL SetDevice(
		MxDeviceEnumerate& p_deviceEnumerate,
		MxDriver* p_driver,
		Direct3DDeviceInfo* p_device
	);

protected:
	BOOL D3DCreate();
	BOOL D3DSetMode();

	int ZBufferDepth(MxAssignedDevice* p_assignedDevice);

	// MxDirect3D::`scalar deleting destructor'

private:
	MxAssignedDevice* m_assignedDevice;
	IDirect3D2* m_pDirect3d;
	IDirect3DDevice2* m_pDirect3dDevice;
	BOOL m_bTexturesDisabled;
	undefined4 m_unk0x890;
};

#endif // MXDIRECT3D_H
