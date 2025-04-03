#ifndef RADIO_H
#define RADIO_H

#include "state.h"
#include "mx_core.h"

class LegoControlManagerNotificationParam;
class MxAtomId;
class MxEndActionNotificationParam;

class RadioState : public LegoState {
public:
	RadioState();

	MxBool IsSerializable() override { return FALSE; }

	static const char* ClassName() { return "RadioState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, RadioState::ClassName()) ||
			   LegoState::IsA(p_name);
	}

	// RadioState::`scalar deleting destructor'

	MxBool IsActive() { return m_active; }

	void SetActive(MxBool p_active) { m_active = p_active; }

	undefined4 FUN_1002d090();
	MxBool FUN_1002d0c0(const MxAtomId& p_atom, MxU32 p_objectId);

	// TODO: Most likely getters/setters are not used according to BETA.

	Playlist m_unk0x08[3];
	MxS16 m_unk0x2c;
	MxBool m_active;
};

class Radio : public MxCore {
public:
	Radio();
	~Radio() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "Radio"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, Radio::ClassName()) || MxCore::IsA(p_name);
	}

	void Initialize(MxBool p_und);
	void CreateState();
	void Play();
	void Stop();

	RadioState* GetState() { return m_state; }

	// Radio::`scalar deleting destructor'

private:
	RadioState* m_state;
	MxBool m_unk0x0c;
	MxBool m_audioEnabled;
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);
};

#endif // RADIO_H
