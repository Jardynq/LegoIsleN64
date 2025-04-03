#ifndef JUKEBOXENTITY_H
#define JUKEBOXENTITY_H

#include "action_sfwd.h"
#include "entity.h"

class JukeBoxEntity : public LegoEntity {
public:
	JukeBoxEntity();
	~JukeBoxEntity() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "JukeBoxEntity"; }

	static MxBool IsA(const char* p_name) {
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
