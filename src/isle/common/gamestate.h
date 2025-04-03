#ifndef LEGOGAMESTATE_H
#define LEGOGAMESTATE_H

#include "action_sfwd.h"
#include "mx_variable.h"

#include <string.h>

class LegoFile;
class LegoState;
class LegoStorage;
class MxVariableTable;
class MxString;

extern const char* g_actorNames[7];

struct ColorStringStruct {
	const char* m_targetName;
	const char* m_colorName;
};

class LegoBackgroundColor : public MxVariable {
public:
	LegoBackgroundColor();
	LegoBackgroundColor(const char* p_key, const char* p_value);

	void SetValue(const char* p_colorString) override;

	void SetLightColor(float p_r, float p_g, float p_b);
	void SetLightColor();
	void ToggleDayNight(MxBool p_sun);
	void ToggleSkyColor();

private:
	float m_h;
	float m_s;
	float m_v;
};

class LegoFullScreenMovie : public MxVariable {
public:
	LegoFullScreenMovie(const char* p_key, const char* p_value);

	void SetValue(const char* p_option) override;
};

class LegoGameState {
public:
	enum Act { e_actNotFound = -1, e_act1, e_act2, e_act3 };

	enum Area {
		e_undefined = 0,
		e_previousArea = 0,
		e_isle,
		e_infomain,
		e_infodoor,
		e_unk4,
		e_elevbott,
		e_elevride,
		e_elevride2,
		e_elevopen,
		e_seaview,
		e_observe,
		e_elevdown,
		e_regbook,
		e_infoscor,
		e_jetrace,
		e_jetrace2,
		e_jetraceExterior,
		e_unk17,
		e_carrace,
		e_carraceExterior,
		e_unk20,
		e_unk21,
		e_pizzeriaExterior,
		e_unk23,
		e_unk24,
		e_garageExterior,
		e_garage,
		e_garadoor,
		e_unk28,
		e_hospitalExterior,
		e_hospital,
		e_unk31,
		e_policeExterior,
		e_unk33,
		e_police,
		e_polidoor,
		e_copterbuild,
		e_dunecarbuild,
		e_jetskibuild,
		e_racecarbuild,
		e_unk40,
		e_unk41,
		e_unk42,
		e_unk43,
		e_unk44,
		e_unk45,
		e_act2main,
		e_act3script,
		e_unk48,
		e_unk49,
		e_unk50,
		e_unk51,
		e_unk52,
		e_jukeboxw,
		e_jukeboxExterior,
		e_unk55,
		e_histbook,
		e_bike,
		e_dunecar,
		e_motocycle,
		e_copter,
		e_skateboard,
		e_ambulance,
		e_towtrack,
		e_jetski,

		e_unk66 = 66
	};

	struct Username {
		Username();
		void Set(Username& p_other) {
			memcpy(m_letters, p_other.m_letters, sizeof(m_letters));
		}

		MxResult Serialize(LegoStorage* p_storage);
		Username& operator=(const Username& p_other);

		MxS16 m_letters[7];
	};

	struct ScoreItem {
		MxResult Serialize(LegoStorage* p_storage);

		MxS16 m_totalScore;
		MxU8 m_scores[5][5];
		Username m_name;
		MxS16 m_unk0x2a;
	};

	struct History {
		History();
		void WriteScoreHistory();
		MxResult Serialize(LegoStorage* p_storage);
		ScoreItem*
		FUN_1003cc90(Username* p_player, MxS16 p_unk0x24, MxS32& p_unk0x2c);

		MxS16 GetCount() { return m_count; }

		// TODO: Not yet correct

		ScoreItem* GetScore(MxS32 p_index) {
			return p_index >= m_count ? NULL : &m_scores[p_index];
		}

		MxS16 m_count;
		ScoreItem m_scores[20];
		MxS16 m_unk0x372;
	};

	LegoGameState();
	~LegoGameState();

	void SetActor(MxU8 p_actorId);
	void RemoveActor();
	void ResetROI();

	MxResult Save(MxULong);
	MxResult DeleteState();
	MxResult Load(MxULong);

	void SerializePlayersInfo(MxS16 p_flags);
	MxResult AddPlayer(Username& p_player);
	void SwitchPlayer(MxS16 p_playerId);
	MxS16 FindPlayer(Username& p_player);

	void SerializeScoreHistory(MxS16 p_flags);
	void SetSavePath(char*);

	LegoState* GetState(const char* p_stateName);
	LegoState* CreateState(const char* p_stateName);

	void GetFileSavePath(MxString* p_outPath, MxS16 p_slotn);
	void StopArea(Area p_area);
	void SwitchArea(Area p_area);
	void Init();

	MxU8 GetActorId() { return m_actorId; }

	const char* GetActorName() { return g_actorNames[GetActorId()]; }

	Act GetCurrentAct() { return m_currentAct; }

	Act GetLoadedAct() { return m_loadedAct; }
	Area GetPreviousArea() { return m_previousArea; }
	Area GetUnknown0x42c() { return m_unk0x42c; }

	void SetDirty(MxBool p_isDirty) { m_isDirty = p_isDirty; }
	void SetPreviousArea(Area p_previousArea) {
		m_previousArea = p_previousArea;
	}
	void SetActorId(MxU8 p_actorId) { m_actorId = p_actorId; }
	void SetUnknown0x42c(Area p_unk0x42c) { m_unk0x42c = p_unk0x42c; }
	Username* GetPlayersIndex(MxS32 p_index) { return &m_players[p_index]; }
	MxS16 GetPlayerCount() { return m_playerCount; }
	LegoBackgroundColor* GetBackgroundColor() { return m_backgroundColor; }

	void SetCurrentAct(Act p_currentAct);
	void FindLoadedAct();
	void RegisterState(LegoState* p_state);

private:
	MxResult WriteVariable(
		LegoStorage* p_storage,
		MxVariableTable* p_from,
		const char* p_variableName
	);
	MxResult WriteEndOfVariables(LegoStorage* p_storage);
	MxS32 ReadVariable(LegoStorage* p_storage, MxVariableTable* p_to);
	void SetColors();
	void SetROIHandlerFunction();

	char* m_savePath;
	MxS16 m_stateCount;
	LegoState** m_stateArray;
	MxU8 m_actorId;
	Act m_currentAct;
	Act m_loadedAct;
	LegoBackgroundColor* m_backgroundColor;
	LegoBackgroundColor* m_tempBackgroundColor;
	LegoFullScreenMovie* m_fullScreenMovie;
	// TODO: Most likely getters/setters are not used according to BETA for the
	// following members:

public:
	MxS16 m_unk0x24;
	MxS16 m_playerCount;
	Username m_players[9];
	History m_history;
	undefined2 m_unk0x41a;
	JukeboxScript::Script m_jukeboxMusic;
	MxBool m_isDirty;
	Area m_currentArea;
	Area m_previousArea;
	Area m_unk0x42c;
};

MxBool ROIHandlerFunction(const char* p_input, char* p_output, MxU32 p_copyLen);

// LegoGameState::ScoreItem::ScoreItem

#endif // LEGOGAMESTATE_H
