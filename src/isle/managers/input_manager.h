#ifndef LEGOINPUTMANAGER_H
#define LEGOINPUTMANAGER_H

#include "event_notification_param.h"
#include "mx_list.h"
#include "mx_presenter.h"
#include "mx_queue.h"

#include <dinput.h>

class LegoCameraController;
class LegoControlManager;
class LegoWorld;

extern MxS32 g_unk0x100f31b0;
extern const char* g_unk0x100f31b4;

// class MxCollection<LegoEventNotificationParam>

// class MxList<LegoEventNotificationParam>

// class MxQueue<LegoEventNotificationParam>

class LegoEventQueue : public MxQueue<LegoEventNotificationParam> {};

// class MxCollection<MxCore*>

// class MxList<MxCore*>

// class MxPtrList<MxCore>

class LegoNotifyList : public MxPtrList<MxCore> {
protected:
	MxS8 Compare(MxCore* p_element1, MxCore* p_element2) override {
		return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1;
	}

public:
	LegoNotifyList(MxBool p_ownership = FALSE)
		: MxPtrList<MxCore>(p_ownership) {}
};

// class MxListCursor<MxCore *>

// class MxPtrListCursor<MxCore>

class LegoNotifyListCursor : public MxPtrListCursor<MxCore> {
public:
	LegoNotifyListCursor(LegoNotifyList* p_list)
		: MxPtrListCursor<MxCore>(p_list) {}
};

class LegoInputManager : public MxPresenter {
public:
	enum Keys {
		c_left = 0x01,
		c_right = 0x02,
		c_up = 0x04,
		c_down = 0x08,
		c_bit5 = 0x10,

		c_leftOrRight = c_left | c_right,
		c_upOrDown = c_up | c_down
	};

	LegoInputManager();
	~LegoInputManager() override;

	void QueueEvent(
		NotificationId p_id,
		MxU8 p_modifier,
		MxLong p_x,
		MxLong p_y,
		MxU8 p_key
	);
	void Register(MxCore*);
	void UnRegister(MxCore*);

	MxResult Tickle() override {
		ProcessEvents();
		return SUCCESS;
	}

	MxResult PutData() override { return SUCCESS; }

	MxResult Create(HWND p_hwnd);
	void Destroy() override;
	void CreateAndAcquireKeyboard(HWND p_hwnd);
	void ReleaseDX();
	MxResult GetJoystickId();
	MxResult GetJoystickState(
		MxU32* p_joystickX,
		MxU32* p_joystickY,
		DWORD* p_buttonsState,
		MxU32* p_povPosition
	);
	void StartAutoDragTimer();
	void StopAutoDragTimer();
	void EnableInputProcessing();
	void SetCamera(LegoCameraController* p_camera);
	void ClearCamera();
	void SetWorld(LegoWorld* p_world);
	void ClearWorld();

	void SetUnknown88(MxBool p_unk0x88) { m_unk0x88 = p_unk0x88; }
	void SetUnknown335(MxBool p_unk0x335) { m_unk0x335 = p_unk0x335; }
	void SetUnknown336(MxBool p_unk0x336) { m_unk0x336 = p_unk0x336; }
	void SetUseJoystick(MxBool p_useJoystick) { m_useJoystick = p_useJoystick; }
	void SetJoystickIndex(MxS32 p_joystickIndex) {
		m_joystickIndex = p_joystickIndex;
	}

	void DisableInputProcessing() {
		m_unk0x88 = TRUE;
		m_unk0x336 = FALSE;
	}

	LegoControlManager* GetControlManager() { return m_controlManager; }

	LegoWorld* GetWorld() { return m_world; }

	LegoCameraController* GetCamera() { return m_camera; }

	void ProcessEvents();
	MxBool ProcessOneEvent(LegoEventNotificationParam& p_param);
	MxBool FUN_1005cdf0(LegoEventNotificationParam& p_param);
	void GetKeyboardState();
	MxResult GetNavigationKeyStates(MxU32& p_keyFlags);

	// LegoInputManager::`scalar deleting destructor'

private:
	MxCriticalSection m_criticalSection;
	LegoNotifyList* m_keyboardNotifyList;
	LegoCameraController* m_camera;
	LegoWorld* m_world;
	LegoEventQueue* m_eventQueue;
	MxS32 m_x;
	MxS32 m_y;
	MxS32 m_unk0x74;
	UINT m_autoDragTimerID;
	UINT m_autoDragTime;
	MxBool m_unk0x80;
	MxBool m_unk0x81;
	LegoControlManager* m_controlManager;
	MxBool m_unk0x88;
	IDirectInput* m_directInput;
	IDirectInputDevice* m_directInputDevice;
	MxBool m_kbStateSuccess;
	MxU8 m_keyboardState[256];
	MxBool m_unk0x195;
	MxS32 m_joyid;
	MxS32 m_joystickIndex;
	JOYCAPS m_joyCaps;
	MxBool m_useJoystick;
	MxBool m_unk0x335;
	MxBool m_unk0x336;
};

// MxCollection<MxCore *>::Compare

// MxCollection<MxCore *>::~MxCollection<MxCore *>

// MxCollection<MxCore *>::Destroy

// MxList<MxCore *>::~MxList<MxCore *>

// LegoNotifyList::`scalar deleting destructor'

// MxPtrList<MxCore>::~MxPtrList<MxCore>

// MxCollection<MxCore *>::`scalar deleting destructor'

// MxList<MxCore *>::`scalar deleting destructor'

// MxPtrList<MxCore>::`scalar deleting destructor'

// LegoNotifyList::~LegoNotifyList

// LegoNotifyListCursor::`scalar deleting destructor'

// MxPtrListCursor<MxCore>::~MxPtrListCursor<MxCore>

// MxListCursor<MxCore *>::`scalar deleting destructor'

// MxPtrListCursor<MxCore>::`scalar deleting destructor'

// MxListCursor<MxCore *>::~MxListCursor<MxCore *>

// LegoNotifyListCursor::~LegoNotifyListCursor

// MxCollection<LegoEventNotificationParam>::Compare

// MxCollection<LegoEventNotificationParam>::~MxCollection<LegoEventNotificationParam>

// MxCollection<LegoEventNotificationParam>::Destroy

// MxList<LegoEventNotificationParam>::~MxList<LegoEventNotificationParam>

// MxCollection<LegoEventNotificationParam>::`scalar deleting destructor'

// MxList<LegoEventNotificationParam>::`scalar deleting destructor'

// LegoEventQueue::`scalar deleting destructor'

// MxQueue<LegoEventNotificationParam>::~MxQueue<LegoEventNotificationParam>

// MxQueue<LegoEventNotificationParam>::`scalar deleting destructor'

// MxListEntry<LegoEventNotificationParam>::GetValue

#endif // LEGOINPUTMANAGER_H
