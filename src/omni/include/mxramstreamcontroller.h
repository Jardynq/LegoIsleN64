#ifndef MXRAMSTREAMCONTROLLER_H
#define MXRAMSTREAMCONTROLLER_H

#include "mxdsbuffer.h"
#include "mxstreamcontroller.h"

class MxDSStreamingAction;

class MxRAMStreamController : public MxStreamController {
public:
	MxRAMStreamController() {}

	const char* ClassName() const override { return "MxRAMStreamController"; }

	MxBool IsA(const char* p_name) const override {
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
