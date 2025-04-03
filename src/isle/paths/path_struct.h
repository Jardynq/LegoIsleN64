#pragma once

#include "mx_atom.h"
#include "mx_notification_param.h"

class LegoPathActor;
class LegoWorld;

class LegoPathStructNotificationParam : public MxNotificationParam {
public:
	LegoPathStructNotificationParam(
		NotificationId p_type,
		MxCore* p_sender,
		MxU8 p_trigger,
		MxS16 p_data
	)
		: MxNotificationParam() {
		m_type = p_type;
		m_sender = p_sender;
		m_data = p_data;
		m_trigger = p_trigger;
	}

	MxNotificationParam* Clone() const override {
		return new LegoPathStructNotificationParam(
			m_type,
			m_sender,
			m_trigger,
			m_data
		);
	}

	MxU8 GetTrigger() { return m_trigger; }

	MxS16 GetData() { return m_data; }

protected:
	MxS16 m_data;
	MxU8 m_trigger;
};

struct LegoPathStructBase {
public:
	enum {
		c_bit1 = 0x01 << 24,
		c_bit2 = 0x02 << 24,
		c_bit3 = 0x04 << 24,
		c_bit4 = 0x08 << 24,
		c_bit5 = 0x10 << 24,
		c_bit6 = 0x20 << 24,
		c_bit7 = 0x40 << 24
	};

	LegoPathStructBase() : m_name(NULL), m_flags(0) {}

	virtual ~LegoPathStructBase() {
		if (m_name != NULL) {
			delete[] m_name;
		}
	}

	char* m_name;
	MxU32 m_flags;
};

class LegoPathStruct : public LegoPathStructBase {
public:
	enum Trigger {
		c_camAnim = 'C',
		c_d = 'D',
		c_e = 'E',
		c_g = 'G',
		c_h = 'H',
		c_music = 'M',
		c_s = 'S',
		c_w = 'W'
	};

	LegoPathStruct() : m_world(NULL) {}

	~LegoPathStruct() override {}

	virtual void
	HandleTrigger(LegoPathActor* p_actor, MxBool p_direction, MxU32 p_data);

	void SetWorld(LegoWorld* p_world) { m_world = p_world; }
	void SetAtomId(const MxAtomId& p_atomId) { m_atomId = p_atomId; }

private:
	MxBool HandleTrigger(
		LegoPathActor* p_actor,
		MxBool p_direction,
		MxU32 p_data,
		MxBool p_bool
	);
	void FUN_1001bc40(const char* p_name, MxU32 p_data, MxBool p_bool);
	void PlayMusic(MxBool p_direction, MxU32 p_data);

	LegoWorld* m_world;
	MxAtomId m_atomId;
};

// LegoPathStructNotificationParam::`scalar deleting destructor'

// LegoPathStructNotificationParam::~LegoPathStructNotificationParam

// LegoPathStructBase::`scalar deleting destructor'

// LegoPathStruct::`vector deleting destructor'

