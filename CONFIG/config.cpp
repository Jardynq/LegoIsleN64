#include "config.h"

#include <direct.h> // _chdir
#include <iostream>
#include <mxdirectx/legodxinfo.h>
#include <mxdirectx/mxdirect3d.h>
#include "../ISLE/MockRegistry.h"
#include <process.h> // _spawnl
#include <stdio.h>
#include <windows.h>

// FUNCTION: CONFIG 0x00402c40
CConfigApp::CConfigApp() {
}

#define MiB (1024 * 1024)

// FUNCTION: CONFIG 0x00402dc0
BOOL CConfigApp::InitInstance() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	m_run_config_dialog = TRUE;
	m_device_enumerator = new LegoDeviceEnumerate;
	if (m_device_enumerator->DoEnumerate()) {
		return FALSE;
	}
	m_driver = NULL;
	m_device = NULL;
	m_full_screen = FALSE;
	m_wide_view_angle = TRUE;
	m_use_joystick = FALSE;
	m_music = TRUE;
	m_flip_surfaces = m_full_screen; // seems dependent
	m_draw_cursor = FALSE; // seems to crash
	m_3d_video_ram = TRUE; // seems to not matter in software emu
	m_joystick_index = -1;
	m_3d_sound = FALSE;
	m_model_quality = 0;
	m_texture_quality = 1;
	m_display_bit_depth = 16;

	m_diskpath = "";
	m_moviespath = "";
	m_savepath = "";
	char* cwd = (char*)calloc(1, PATH_MAX);
	if (getcwd(cwd, PATH_MAX) != NULL) {
		m_diskpath = cwd;
		m_moviespath = cwd;
		m_savepath = cwd;
	}
	else {
		printf("Failed to get cwd\n");
	}

	return 0;
}

// FUNCTION: CONFIG 0x004031b0
BOOL CConfigApp::WriteReg(const char* p_key, const char* p_value) const {
	printf("Write str %s : %s\n", p_key, p_value);
	return RegWriteKey(p_key, RegString, p_value);
}

BOOL CConfigApp::WriteRegBool(const char* p_key, BOOL value) const {
	printf("Write bol %s : %d\n", p_key, value);
	return RegWriteKey(p_key, RegBool, &value);
}

BOOL CConfigApp::WriteRegInt(const char* p_key, int value) const {
	printf("Write int %s : %d\n", p_key, value);
	return RegWriteKey(p_key, RegInt, &value);
}

// FUNCTION: CONFIG 0x00403240
BOOL CConfigApp::ReadReg(LPCSTR p_key, LPCSTR p_value, DWORD p_size) const {
	int result = RegReadKey(p_key, RegString, (char*)p_value, p_size);
	printf("Read str %d, %d, %s : %s\n", result, p_size, p_key, p_value);
	return result;
}

// FUNCTION: CONFIG 0x004032b0
BOOL CConfigApp::ReadRegBool(LPCSTR p_key, BOOL* p_bool) const {
	int result = RegReadKey(p_key, RegBool, p_bool, 16);
	printf("Read bol %d, %s : %d\n", result, p_key, *p_bool);
	return result;
}

// FUNCTION: CONFIG 0x00403380
BOOL CConfigApp::ReadRegInt(LPCSTR p_key, int* p_value) const {
	int result = RegReadKey(p_key, RegInt, p_value, 16);
	printf("Read int %d, %s : %d\n", result, p_key, *p_value);
	return result;
}

// FUNCTION: CONFIG 0x004033d0
BOOL CConfigApp::IsDeviceInBasicRGBMode() const {
	/*
	 * BUG: should be:
	 *  return !GetHardwareDeviceColorModel() && (m_device->m_HELDesc.dcmColorModel & D3DCOLOR_RGB);
	 */
	return !GetHardwareDeviceColorModel() && m_device->m_HELDesc.dcmColorModel == D3DCOLOR_RGB;
}

// FUNCTION: CONFIG 0x00403400
D3DCOLORMODEL CConfigApp::GetHardwareDeviceColorModel() const {
	return m_device->m_HWDesc.dcmColorModel;
}

// FUNCTION: CONFIG 0x00403410
BOOL CConfigApp::IsPrimaryDriver() const {
	return m_driver == &m_device_enumerator->GetDriverList().front();
}


void PrintD3DDeviceDesc(const D3DDEVICEDESC* desc) {
	if (!desc) {
		printf("Invalid D3D Device Descriptor!\n");
		return;
	}

	printf("=============== D3D Device Descriptor ===============\n");
	printf("Size: %lu bytes\n", desc->dwSize);
	printf("Flags: 0x%08lx\n", desc->dwFlags);
	printf("Color Model: %s\n", (desc->dcmColorModel == D3DCOLOR_MONO) ? "Monochrome" : "RGB");
	printf("Device Capabilities: 0x%08lx\n", desc->dwDevCaps);
	printf("Supports Clipping: %s\n", desc->bClipping ? "Yes" : "No");

	// Transform capabilities
	printf("\n-- Transform Capabilities --\n");
	printf("  Size: %lu\n", desc->dtcTransformCaps.dwSize);
	printf("  Caps: 0x%08lx\n", desc->dtcTransformCaps.dwCaps);

	// Lighting capabilities
	printf("\n-- Lighting Capabilities --\n");
	printf("  Size: %lu\n", desc->dlcLightingCaps.dwSize);
	printf("  Caps: 0x%08lx\n", desc->dlcLightingCaps.dwCaps);
	printf("  Max Active Lights: %lu\n", desc->dlcLightingCaps.dwNumLights);
	printf("  Lighting Model: %lu\n", desc->dlcLightingCaps.dwLightingModel);

	// Line Caps
	printf("\n-- Line Capabilities --\n");
	printf("  Misc Caps: 0x%08lx\n", desc->dpcLineCaps.dwMiscCaps);
	printf("  Raster Caps: 0x%08lx\n", desc->dpcLineCaps.dwRasterCaps);
	printf("  ZCmp Caps: 0x%08lx\n", desc->dpcLineCaps.dwZCmpCaps);
	printf("  SrcBlend Caps: 0x%08lx\n", desc->dpcLineCaps.dwSrcBlendCaps);
	printf("  DestBlend Caps: 0x%08lx\n", desc->dpcLineCaps.dwDestBlendCaps);

	// Triangle Caps
	printf("\n-- Triangle Capabilities --\n");
	printf("  Misc Caps: 0x%08lx\n", desc->dpcTriCaps.dwMiscCaps);
	printf("  Raster Caps: 0x%08lx\n", desc->dpcTriCaps.dwRasterCaps);
	printf("  ZCmp Caps: 0x%08lx\n", desc->dpcTriCaps.dwZCmpCaps);
	printf("  SrcBlend Caps: 0x%08lx\n", desc->dpcTriCaps.dwSrcBlendCaps);
	printf("  DestBlend Caps: 0x%08lx\n", desc->dpcTriCaps.dwDestBlendCaps);

	// Depth Buffers
	printf("\n-- Depth & Buffer Information --\n");
	printf("  Render Bit Depth: %lu\n", desc->dwDeviceRenderBitDepth);
	printf("  Z-Buffer Bit Depth: %lu\n", desc->dwDeviceZBufferBitDepth);
	printf("  Max Buffer Size: %lu\n", desc->dwMaxBufferSize);
	printf("  Max Vertex Count: %lu\n", desc->dwMaxVertexCount);

	// Texture Information
	printf("\n-- Texture Capabilities --\n");
	printf("  Min Texture Size: %lux%lu\n", desc->dwMinTextureWidth, desc->dwMinTextureHeight);
	printf("  Max Texture Size: %lux%lu\n", desc->dwMaxTextureWidth, desc->dwMaxTextureHeight);
	printf("  Min Stipple Size: %lux%lu\n", desc->dwMinStippleWidth, desc->dwMinStippleHeight);
	printf("  Max Stipple Size: %lux%lu\n", desc->dwMaxStippleWidth, desc->dwMaxStippleHeight);
	printf("======================================================\n");
}

// FUNCTION: CONFIG 0x00403430
BOOL CConfigApp::ReadRegisterSettings() {
	char buffer[256];
	BOOL is_modified = FALSE;
	int tmp = -1;

	is_modified = TRUE;
	m_device_enumerator->FUN_1009d210();
	tmp = m_device_enumerator->FUN_1009d0d0();
	LPDIRECTDRAW dd;
	if (DirectDrawCreate(NULL, &dd, 0) != DD_OK) {
		printf("Failed to create DD\n");
	}

	int index = 0;
	while (1) {
		if (m_device_enumerator->GetDevice(index++, m_driver, m_device) == -1) {
			break;
		}
		printf("%s\n:", m_device->m_deviceName);
		printf("%s\n:", m_device->m_deviceDesc);
		PrintD3DDeviceDesc(&m_device->m_HWDesc);
		PrintD3DDeviceDesc(&m_device->m_HELDesc);
	}

	m_device_enumerator->GetDevice(4, m_driver, m_device);
	return 0;
}

// FUNCTION: CONFIG 0x00403630
BOOL CConfigApp::ValidateSettings() {
	BOOL is_modified = FALSE;

	if (!IsPrimaryDriver() && !m_full_screen) {
		m_full_screen = TRUE;
		is_modified = TRUE;
	}
	if (IsDeviceInBasicRGBMode()) {
		if (m_3d_video_ram) {
			m_3d_video_ram = FALSE;
			is_modified = TRUE;
		}
		if (m_flip_surfaces) {
			m_flip_surfaces = FALSE;
			is_modified = TRUE;
		}
		if (m_display_bit_depth != 16) {
			m_display_bit_depth = 16;
			is_modified = TRUE;
		}
	}
	if (!GetHardwareDeviceColorModel()) {
		m_draw_cursor = FALSE;
		is_modified = TRUE;
	}
	else {
		if (!m_3d_video_ram) {
			m_3d_video_ram = TRUE;
			is_modified = TRUE;
		}
		if (m_full_screen && !m_flip_surfaces) {
			m_flip_surfaces = TRUE;
			is_modified = TRUE;
		}
	}
	if (m_flip_surfaces) {
		if (!m_3d_video_ram) {
			m_3d_video_ram = TRUE;
			is_modified = TRUE;
		}
		if (!m_full_screen) {
			m_full_screen = TRUE;
			is_modified = TRUE;
		}
	}
	if ((m_display_bit_depth != 8 && m_display_bit_depth != 16) && (m_display_bit_depth != 0 || m_full_screen)) {
		m_display_bit_depth = 8;
		is_modified = TRUE;
	}
	if (m_model_quality < 0 || m_model_quality > 2) {
		m_model_quality = 1;
		is_modified = TRUE;
	}
	if (m_texture_quality < 0 || m_texture_quality > 1) {
		m_texture_quality = 0;
		is_modified = TRUE;
	}
	return is_modified;
}

// FUNCTION: CONFIG 0x004037a0
DWORD CConfigApp::GetConditionalDeviceRenderBitDepth() const {
	if (IsDeviceInBasicRGBMode()) {
		return 0;
	}
	if (GetHardwareDeviceColorModel()) {
		return 0;
	}
	return m_device->m_HELDesc.dwDeviceRenderBitDepth & 0x800;
}

// FUNCTION: CONFIG 0x004037e0
DWORD CConfigApp::GetDeviceRenderBitStatus() const {
	if (GetHardwareDeviceColorModel()) {
		return m_device->m_HWDesc.dwDeviceRenderBitDepth & 0x400;
	}
	else {
		return m_device->m_HELDesc.dwDeviceRenderBitDepth & 0x400;
	}
}

// FUNCTION: CONFIG 0x00403810
BOOL CConfigApp::AdjustDisplayBitDepthBasedOnRenderStatus() {
	if (m_display_bit_depth == 8) {
		if (GetConditionalDeviceRenderBitDepth()) {
			return FALSE;
		}
	}
	if (m_display_bit_depth == 16) {
		if (GetDeviceRenderBitStatus()) {
			return FALSE;
		}
	}
	if (GetConditionalDeviceRenderBitDepth()) {
		m_display_bit_depth = 8;
		return TRUE;
	}
	if (GetDeviceRenderBitStatus()) {
		m_display_bit_depth = 16;
		return TRUE;
	}
	m_display_bit_depth = 8;
	return TRUE;
}

// FUNCTION: CONFIG 00403890
void CConfigApp::WriteRegisterSettings() const {
	char buffer[128];

	m_device_enumerator->FormatDeviceName(buffer, m_driver, m_device);
	WriteReg("3D Device ID", buffer);
	WriteReg("3D Device Name", m_device->m_deviceName);
	WriteRegInt("Display Bit Depth", m_display_bit_depth);
	WriteRegBool("Flip Surfaces", m_flip_surfaces);
	WriteRegBool("Full Screen", m_full_screen);
	WriteRegBool("Back Buffers in Video RAM", m_3d_video_ram);
	WriteRegBool("Wide View Angle", m_wide_view_angle);
	WriteRegBool("3DSound", m_3d_sound);
	WriteRegBool("Draw Cursor", m_draw_cursor);
	WriteRegInt("Island Quality", m_model_quality);
	WriteRegInt("Island Texture", m_texture_quality);
	WriteRegBool("UseJoystick", m_use_joystick);
	WriteRegBool("Music", m_music);
	WriteRegInt("JoystickIndex", m_joystick_index);
	WriteReg("diskpath", m_diskpath);
	WriteReg("moviespath", m_moviespath);
	WriteReg("savepath", m_savepath);
}

// FUNCTION: CONFIG 0x00403a90
int CConfigApp::ExitInstance() {
	if (m_device_enumerator) {
		delete m_device_enumerator;
		m_device_enumerator = NULL;
	}
	return 0;
}

// GLOBAL: CONFIG 0x00408e50
CConfigApp g_theApp;

int main() {
	RegReset();
	g_theApp.InitInstance();
	g_theApp.ReadRegisterSettings();
	//g_theApp.ValidateSettings();
	g_theApp.WriteRegisterSettings();
	char input[100];
	printf("Enter text: ");
	fgets(input, sizeof(input), stdin);
	return 0;
}
