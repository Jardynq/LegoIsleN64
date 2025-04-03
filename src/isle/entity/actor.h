#pragma once

#include "entity.h"
#include "mx_matrix.h"

class LegoCacheSound;

class LegoActor : public LegoEntity {
public:
	enum { c_none = 0, c_pepper, c_mama, c_papa, c_nick, c_laura, c_brickster };

	LegoActor();
	~LegoActor() override;

	static const char* ClassName() { return "LegoActor"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoActor::ClassName()) ||
			   LegoEntity::IsA(p_name);
	}

	void ParseAction(char* p_extra) override;
	void SetROI(LegoROI* p_roi, MxBool p_bool1, MxBool p_bool2) override;

	virtual MxFloat GetSoundFrequencyFactor() { return m_frequencyFactor; }

	virtual void SetSoundFrequencyFactor(MxFloat p_frequencyFactor) {
		m_frequencyFactor = p_frequencyFactor;
	}

	virtual void VTable0x58(MxFloat p_unk0x70) { m_unk0x70 = p_unk0x70; }

	virtual MxFloat VTable0x5c() { return m_unk0x70; }

	virtual MxU8 GetActorId() { return m_actorId; }

	virtual void SetActorId(MxU8 p_actorId) { m_actorId = p_actorId; }

	static const char* GetActorName(MxU8 p_id);

	void Mute(MxBool p_muted);

protected:
	MxFloat m_frequencyFactor;
	LegoCacheSound* m_sound;
	MxFloat m_unk0x70;
	MxU8 m_actorId;
};

// LegoActor::`scalar deleting destructor'

