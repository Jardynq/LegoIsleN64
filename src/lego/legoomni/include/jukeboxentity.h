#ifndef JUKEBOXENTITY_H
#define JUKEBOXENTITY_H

#include "actionsfwd.h"
#include "legoentity.h"

class JukeBoxEntity : public LegoEntity {
public:
	JukeBoxEntity();
	~JukeBoxEntity() override;

	MxLong Notify(MxParam& p_param) override;

	const char* ClassName() const override { return "JukeBoxEntity"; }

	MxBool IsA(const char* p_name) const override {
		return !strcmp(p_name, JukeBoxEntity::ClassName()) ||
			   LegoEntity::IsA(p_name);
	}

	void StartAction();
	void StopAction(JukeboxScript::Script p_script);

	MxBool IsBackgroundAudioEnabled() { return m_audioEnabled; }

	// JukeBoxEntity::`scalar deleting destructor'

protected:
	MxBool m_audioEnabled;
};

#endif // JUKEBOXENTITY_H
