#ifndef MXDIRECTXINFO_H
#define MXDIRECTXINFO_H

#include <d3d.h>

struct DeviceModesInfo {

	struct Mode {
		int operator==(const Mode& p_mode) const {
			return (
				(width == p_mode.width) && (height == p_mode.height) &&
				(bitsPerPixel == p_mode.bitsPerPixel)
			);
		}

		int width;
		int height;
		int bitsPerPixel;
	};

	DeviceModesInfo();
	~DeviceModesInfo();

	GUID* m_guid;
	Mode* m_modeArray;
	int m_count;
	DDCAPS m_ddcaps;
	void* m_unk0x178;

	// DeviceModesInfo::`scalar deleting destructor'
};

class MxAssignedDevice {
public:
	enum { c_hardwareMode = 0x01, c_primaryDevice = 0x02 };

	MxAssignedDevice();
	~MxAssignedDevice();

	unsigned int GetFlags() { return m_flags; }
	BOOL GetHardwareMode() { return ((int) m_flags << 31) >> 31; }
	D3DDEVICEDESC& GetDesc() { return m_desc; }

	friend class MxDirect3D;

	// MxAssignedDevice::`scalar deleting destructor'

private:
	GUID m_guid;
	unsigned int m_flags;
	D3DDEVICEDESC m_desc;
	DeviceModesInfo* m_deviceInfo;
};

struct Direct3DDeviceInfo {
	Direct3DDeviceInfo() {}
	~Direct3DDeviceInfo();
	Direct3DDeviceInfo(
		LPGUID p_guid,
		LPSTR p_deviceDesc,
		LPSTR p_deviceName,
		LPD3DDEVICEDESC p_HWDesc,
		LPD3DDEVICEDESC p_HELDesc
	);

	void Initialize(
		LPGUID p_guid,
		LPSTR p_deviceDesc,
		LPSTR p_deviceName,
		LPD3DDEVICEDESC p_HWDesc,
		LPD3DDEVICEDESC p_HELDesc
	);

	LPGUID m_guid;
	char* m_deviceDesc;
	char* m_deviceName;
	D3DDEVICEDESC m_HWDesc;
	D3DDEVICEDESC m_HELDesc;
	int operator==(const Direct3DDeviceInfo&) const { return 0; }
	int operator<(const Direct3DDeviceInfo&) const { return 0; }
};

struct MxDisplayMode {
	MxDisplayMode() {}

	MxDisplayMode(DWORD p_width, DWORD p_height, DWORD p_bitsPerPixel)
		: m_width(p_width), m_height(p_height), m_bitsPerPixel(p_bitsPerPixel) {

	}

	int operator==(MxDisplayMode) const { return 0; }
	int operator<(MxDisplayMode) const { return 0; }

	DWORD m_width;
	DWORD m_height;
	DWORD m_bitsPerPixel;
};

struct MxDriver {
	MxDriver() {}
	~MxDriver();
	MxDriver(LPGUID p_guid);
	MxDriver(LPGUID p_guid, LPSTR p_driverDesc, LPSTR p_driverName);

	void Init(LPGUID p_guid, LPSTR p_driverDesc, LPSTR p_driverName);

	LPGUID m_guid;
	char* m_driverDesc;
	char* m_driverName;
	DDCAPS m_ddCaps;
	list<Direct3DDeviceInfo> m_devices;
	list<MxDisplayMode> m_displayModes;
	int operator==(const MxDriver&) const { return 0; }
	int operator<(const MxDriver&) const { return 0; }
};

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo>
// >::~list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >

// list<MxDisplayMode,allocator<MxDisplayMode>
// >::~list<MxDisplayMode,allocator<MxDisplayMode> >

// List<Direct3DDeviceInfo>::~List<Direct3DDeviceInfo>

// List<MxDisplayMode>::~List<MxDisplayMode>

// list<MxDriver,allocator<MxDriver> >::~list<MxDriver,allocator<MxDriver> >

// List<MxDriver>::~List<MxDriver>

// Compiler-generated copy ctor for MxDriver

// ??0MxDriver@@QAE@ABU0@@Z

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::insert

// list<MxDisplayMode,allocator<MxDisplayMode> >::insert

// MxDriver::`scalar deleting destructor'

// Direct3DDeviceInfo::`scalar deleting destructor'

class MxDeviceEnumerate {
public:
	MxDeviceEnumerate();
	~MxDeviceEnumerate();

	virtual int DoEnumerate();

	BOOL EnumDirectDrawCallback(
		LPGUID p_guid,
		LPSTR p_driverDesc,
		LPSTR p_driverName
	);
	HRESULT EnumDisplayModesCallback(LPDDSURFACEDESC p_ddsd);
	HRESULT EnumDevicesCallback(
		LPGUID p_guid,
		LPSTR p_deviceDesc,
		LPSTR p_deviceName,
		LPD3DDEVICEDESC p_HWDesc,
		LPD3DDEVICEDESC p_HELDesc
	);
	const char* EnumerateErrorToString(HRESULT p_error);
	static BOOL CALLBACK DirectDrawEnumerateCallback(
		LPGUID p_guid,
		LPSTR p_driverDesc,
		LPSTR p_driverName,
		LPVOID p_context
	);
	static HRESULT CALLBACK
	DisplayModesEnumerateCallback(LPDDSURFACEDESC p_ddsd, LPVOID p_context);
	static HRESULT CALLBACK DevicesEnumerateCallback(
		LPGUID p_guid,
		LPSTR p_deviceDesc,
		LPSTR p_deviceName,
		LPD3DDEVICEDESC p_HWDesc,
		LPD3DDEVICEDESC p_HELDesc,
		LPVOID p_context
	);

	friend class MxDirect3D;

	const list<MxDriver>& GetDriverList() const { return m_list; }

	struct GUID4 {
		int m_data1;
		int m_data2;
		int m_data3;
		int m_data4;

		static unsigned char Compare(const GUID4& p_a, const GUID4& p_b) {
			return p_a.m_data1 == p_b.m_data1 && p_a.m_data2 == p_b.m_data2 &&
				   p_a.m_data3 == p_b.m_data3 && p_a.m_data4 == p_b.m_data4;
		}
	};

	unsigned char IsInitialized() const { return m_initialized; }

protected:
	list<MxDriver> m_list;
	unsigned char m_initialized;
};

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::iterator::operator*

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::iterator::operator++

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::begin

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::end

// list<MxDriver,allocator<MxDriver> >::iterator::operator*

// list<MxDriver,allocator<MxDriver> >::iterator::operator++

// list<MxDriver,allocator<MxDriver> >::iterator::operator++

// list<MxDriver,allocator<MxDriver> >::_Acc::_Next

// list<MxDriver,allocator<MxDriver> >::begin

// list<MxDriver,allocator<MxDriver> >::iterator::iterator

// list<MxDriver,allocator<MxDriver> >::end

// ??9@YAHABViterator@?$list@UMxDriver@@V?$allocator@UMxDriver@@@@@@0@Z

// ??9@YAHABViterator@?$list@UDirect3DDeviceInfo@@V?$allocator@UDirect3DDeviceInfo@@@@@@0@Z

// list<MxDriver,allocator<MxDriver> >::size

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::size

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::erase

// list<MxDriver,allocator<MxDriver> >::erase

// list<MxDriver,allocator<MxDriver> >::_Freenode

// list<MxDriver,allocator<MxDriver> >::front

// list<MxDriver,allocator<MxDriver> >::back

// list<MxDriver,allocator<MxDriver> >::iterator::operator--

// list<MxDriver,allocator<MxDriver> >::push_back

// list<MxDriver,allocator<MxDriver> >::insert

// list<MxDisplayMode,allocator<MxDisplayMode> >::push_back

// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::push_back

#endif // MXDIRECTXINFO_H
