#ifndef LEGOACTIONCONTROLPRESENTER_H
#define LEGOACTIONCONTROLPRESENTER_H

#include "extra.h"
#include "mxmediapresenter.h"
#include "mxstring.h"

class LegoActionControlPresenter : public MxMediaPresenter {
public:
	LegoActionControlPresenter() : m_unk0x50(Extra::ActionType::e_none) {}
	~LegoActionControlPresenter() override { Destroy(TRUE); }

	static const char* HandlerClassName() {

		return "LegoActionControlPresenter";
	}

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoActionControlPresenter::ClassName()) ||
			   MxMediaPresenter::IsA(p_name);
	}

	void ReadyTickle() override;
	void RepeatingTickle() override;
	void ParseExtra() override;
	MxResult AddToManager() override;
	virtual void Destroy(MxBool p_fromDestructor);

private:
	Extra::ActionType m_unk0x50;
	MxString m_unk0x54;
	undefined4 m_unk0x64;
};

// LegoActionControlPresenter::`scalar deleting destructor'

#endif // LEGOACTIONCONTROLPRESENTER_H
