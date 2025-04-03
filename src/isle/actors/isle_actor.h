#pragma once

#include "actor.h"

class LegoControlManagerNotificationParam;
class LegoPathStructNotificationParam;
class LegoWorld;
class MxEndActionNotificationParam;
class MxNotificationParam;

class IsleActor : public LegoActor {
public:
	MxLong Notify(MxParam& p_param) override;
	MxResult Create(MxDSAction& p_dsAction) override;

	virtual MxLong HandleClick() { return 0; }

	virtual MxLong VTable0x6c() { return 0; }

	virtual MxLong HandleEndAnim() { return 0; }

	virtual MxLong HandleEndAction(MxEndActionNotificationParam&) { return 0; }

	virtual MxLong HandleButtonDown(LegoControlManagerNotificationParam&) {
		return 0;
	}

	virtual MxLong HandleButtonUp(LegoControlManagerNotificationParam&) {
		return 0;
	}

	virtual MxLong HandlePathStruct(LegoPathStructNotificationParam&) {
		return 0;
	}

	static const char* ClassName() { return "IsleActor"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, IsleActor::ClassName()) ||
			   LegoActor::IsA(p_name);
	}

protected:
	LegoWorld* m_world;
};

// IsleActor::~IsleActor

// IsleActor::`scalar deleting destructor'

