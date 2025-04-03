#ifndef MXRAMSTREAMCONTROLLER_H
#define MXRAMSTREAMCONTROLLER_H

#include "mx_ds_buffer.h"
#include "mx_stream_controller.h"

class MxDSStreamingAction;

class MxRAMStreamController : public MxStreamController {
public:
	MxRAMStreamController() {}

	static const char* ClassName() { return "MxRAMStreamController"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, MxRAMStreamController::ClassName()) ||
			   !strcmp(p_name, MxStreamController::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	MxResult Open(const char* p_filename) override;
	MxResult VTable0x20(MxDSAction* p_action) override;
	MxResult VTable0x24(MxDSAction* p_action) override;

private:
	MxDSBuffer m_buffer;
	MxResult DeserializeObject(MxDSStreamingAction& p_action);
};

// MxRAMStreamController::`scalar deleting destructor'

#endif // MXRAMSTREAMCONTROLLER_H
