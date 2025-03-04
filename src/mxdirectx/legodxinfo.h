#ifndef LEGODXINFO_H
#define LEGODXINFO_H

#include "mxdirectxinfo.h"

class LegoDeviceEnumerate : public MxDeviceEnumerate {
public:
	int ParseDeviceName(const char* p_deviceId);
	int ProcessDeviceBytes(int p_deviceNum, GUID& p_guid);
	int GetDevice(
		int p_deviceNum,
		MxDriver*& p_driver,
		Direct3DDeviceInfo*& p_device
	);
	int FormatDeviceName(
		char* p_buffer,
		const MxDriver* p_ddInfo,
		const Direct3DDeviceInfo* p_d3dInfo
	) const;
	int BETA_1011cc65(int p_idx, char* p_buffer);
	int FUN_1009d0d0();
	static int SupportsMMX();
	static int SupportsCPUID();
	int FUN_1009d210();
	unsigned char DriverSupportsRequiredDisplayMode(MxDriver& p_driver);
	unsigned char FUN_1009d3d0(Direct3DDeviceInfo& p_device);

	// LegoDeviceEnumerate::LegoDeviceEnumerate

	// LegoDeviceEnumerate::~LegoDeviceEnumerate
};

#endif // LEGODXINFO_H
