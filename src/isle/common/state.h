#ifndef LEGOSTATE_H
#define LEGOSTATE_H

#include "storage.h"
#include "mx_core.h"

class LegoState : public MxCore {
public:
	enum ScoreColor { e_grey = 0, e_yellow, e_blue, e_red };

	struct Playlist {
		enum Mode { e_loop, e_once, e_random, e_loopSkipFirst };

		Playlist()
			: m_objectIds(NULL), m_length(0), m_mode(e_loop), m_nextIndex(0) {}

		Playlist(MxU32* p_objectIds, MxS16 p_length, MxS16 p_mode)
			: m_objectIds(p_objectIds), m_length(p_length), m_mode(p_mode),
			  m_nextIndex(0) {}

		Playlist& operator=(const Playlist& p_playlist) {
			m_objectIds = p_playlist.m_objectIds;
			m_length = p_playlist.m_length;
			m_nextIndex = p_playlist.m_nextIndex;
			m_mode = p_playlist.m_mode;
			return *this;
		}

		MxU32 Next();
		MxBool Contains(MxU32 p_objectId);

		MxU32* m_objectIds;
		MxS16 m_length;
		MxS16 m_mode;
		MxS16 m_nextIndex;
	};

	~LegoState() override {}

	virtual MxBool IsSerializable() { return TRUE; }

	virtual MxBool Reset() { return FALSE; }

	virtual MxResult Serialize(LegoStorage* p_storage) {
		if (p_storage->IsWriteMode()) {
			p_storage->WriteMxString(ClassName());
		}
		return SUCCESS;
	}

	static const char* ClassName() { return "LegoState"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoState::ClassName()) || MxCore::IsA(p_name);
	}

	// LegoState::`scalar deleting destructor'
};

#endif // LEGOSTATE_H
