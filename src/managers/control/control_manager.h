#ifndef LEGOCONTROLMANAGER_H
#define LEGOCONTROLMANAGER_H

#include "event_notification_param.h"
#include "input_manager.h"
#include "mx_core.h"
#include "mx_presenter_list.h"

class MxControlPresenter;

class LegoControlManagerNotificationParam : public LegoEventNotificationParam {
public:
	LegoControlManagerNotificationParam() : LegoEventNotificationParam() {
		m_clickedObjectId = -1;
		m_clickedAtom = NULL;
	}

	// TODO: Most likely getters/setters are not used according to BETA.

	MxS32 GetClickedObjectId() const { return m_clickedObjectId; }
	const char* GetClickedAtom() const { return m_clickedAtom; }
	MxS16 GetUnknown0x28() const { return m_unk0x28; }

	void SetClickedObjectId(MxS32 p_clickedObjectId) {
		m_clickedObjectId = p_clickedObjectId;
	}
	void SetClickedAtom(const char* p_clickedAtom) {
		m_clickedAtom = p_clickedAtom;
	}
	void SetUnknown0x28(MxS16 p_unk0x28) { m_unk0x28 = p_unk0x28; }

	MxS32 m_clickedObjectId;
	const char* m_clickedAtom;
	MxS16 m_unk0x28;
};

// LegoControlManagerNotificationParam::`scalar deleting destructor'

// LegoControlManagerNotificationParam::~LegoControlManagerNotificationParam

class LegoControlManager : public MxCore {
public:
	LegoControlManager();
	~LegoControlManager() override;

	MxResult Tickle() override;

	static const char* HandlerClassName() { return "LegoControlManager"; }

	static const char* ClassName() { return HandlerClassName(); }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoControlManager::ClassName()) ||
			   MxCore::IsA(p_name);
	}

	void FUN_10028df0(MxPresenterList* p_presenterList);
	void Register(MxCore* p_listener);
	void Unregister(MxCore* p_listener);
	MxBool
	FUN_10029210(LegoEventNotificationParam& p_param, MxPresenter* p_presenter);
	void FUN_100293c0(MxU32 p_objectId, const char* p_atom, MxS16 p_unk0x4e);
	MxControlPresenter* FUN_100294e0(MxS32 p_x, MxS32 p_y);
	MxBool FUN_10029630();
	MxBool FUN_10029750();
	void FUN_100292e0();

	undefined4 GetUnknown0x0c() { return m_unk0x0c; }
	undefined GetUnknown0x10() { return m_unk0x10; }

	// LegoControlManager::`scalar deleting destructor'

private:
	undefined4 m_unk0x08;
	undefined4 m_unk0x0c;
	MxBool m_unk0x10;
	MxPresenter* m_unk0x14;
	LegoControlManagerNotificationParam m_event;
	MxPresenterList* m_presenterList;
	LegoNotifyList m_notifyList;
};

#endif // LEGOCONTROLMANAGER_H
