#pragma once

#include "mx_ds_action.h"
#include "mx_omni.h"

class Isle;
class LegoAnimationManager;
class LegoBuildingManager;
class LegoCharacterManager;
class LegoEntity;
class LegoGameState;
class LegoInputManager;
class LegoNavController;
class LegoPathActor;
class LegoPathBoundary;
class LegoPlantManager;
class LegoROI;
class LegoSoundManager;
class LegoTextureContainer;
class LegoVideoManager;
class LegoWorld;
class LegoWorldList;
class MxAtomId;
class MxBackgroundAudioManager;
class MxTransitionManager;
class ViewLODListManager;

class LegoOmni : public MxOmni {
public:
	enum { c_disableInput = 0x01, c_disable3d = 0x02, c_clearScreen = 0x04 };

	enum World {
		e_undefined = -1,
		e_act1 = 0,
		e_imain,
		e_icube,
		e_ireg,
		e_ielev,
		e_iisle,
		e_hosp,
		e_police,
		e_gmain,
		e_bldh,
		e_bldd,
		e_bldj,
		e_bldr,
		e_racc,
		e_racj,
		e_act2,
		e_act3,
		e_test,
		e_numWorlds = e_test + 2 // count e_undefined
	};

	struct WorldContainer {

		WorldContainer() : m_id(e_undefined), m_atomId(NULL) {}

		WorldContainer(World p_id, const char* p_key, MxAtomId* p_atomId)
			: m_id(p_id) {

			if (p_key) {
				strcpy(m_key, p_key);
			}

			m_atomId = p_atomId;
		}

		WorldContainer& operator=(const WorldContainer& p_container) {
			m_id = p_container.m_id;
			strcpy(m_key, p_container.m_key);
			m_atomId = p_container.m_atomId;
			return *this;
		}

		World GetId() { return m_id; }
		const char* GetKey() { return m_key; }

		World m_id;
		char m_key[20];
		MxAtomId* m_atomId;
	};

	LegoOmni();
	~LegoOmni() override;

	MxLong Notify(MxParam& p_param) override;

	static const char* ClassName() { return "LegoOmni"; }

	static MxBool IsA(const char* p_name) {
		return !strcmp(p_name, LegoOmni::ClassName()) || MxOmni::IsA(p_name);
	}

	void Init() override;
	MxResult Create(MxOmniCreateParam& p_param) override;
	void Destroy() override;
	MxResult Start(MxDSAction* p_dsAction) override;
	void DeleteObject(MxDSAction& p_dsAction) override;
	MxBool DoesEntityExist(MxDSAction& p_dsAction) override;
	MxEntity*
	AddToWorld(const char* p_id, MxS32 p_entityId, MxPresenter* p_presenter)
		override;
	void NotifyCurrentEntity(const MxNotificationParam& p_param) override;
	void Pause() override;
	void Resume() override;

	LegoWorld* FindWorld(const MxAtomId& p_atom, MxS32 p_entityid);
	LegoROI* FindROI(const char* p_name);
	void AddWorld(LegoWorld* p_world);
	void DeleteWorld(LegoWorld* p_world);
	void FUN_1005b4f0(MxBool p_disable, MxU16 p_flags);
	void CreateBackgroundAudio();
	void RemoveWorld(const MxAtomId& p_atom, MxLong p_objectId);
	MxResult RegisterWorlds();
	const char* GetWorldName(LegoOmni::World p_id);
	MxAtomId* GetWorldAtom(LegoOmni::World p_id);
	World GetWorldId(const char* p_key);
	void DeleteAction();

	static MxS32 GetCurrPathInfo(LegoPathBoundary**, MxS32&);
	static void CreateInstance();
	static LegoOmni* GetInstance();

	LegoVideoManager* GetVideoManager() {
		return (LegoVideoManager*) m_videoManager;
	}
	LegoSoundManager* GetSoundManager() {
		return (LegoSoundManager*) m_soundManager;
	}

	LegoInputManager* GetInputManager() { return m_inputManager; }

	LegoTextureContainer* GetTextureContainer() { return m_textureContainer; }
	ViewLODListManager* GetViewLODListManager() { return m_viewLODListManager; }
	LegoWorld* GetCurrentWorld() { return m_currentWorld; }
	LegoNavController* GetNavController() { return m_navController; }
	LegoPathActor* GetUserActor() { return m_userActor; }

	LegoPlantManager* GetPlantManager() { return m_plantManager; }

	LegoAnimationManager* GetAnimationManager() { return m_animationManager; }

	LegoBuildingManager* GetBuildingManager() { return m_buildingManager; }

	LegoGameState* GetGameState() { return m_gameState; }

	MxBackgroundAudioManager* GetBackgroundAudioManager() {
		return m_bkgAudioManager;
	}

	MxTransitionManager* GetTransitionManager() { return m_transitionManager; }
	MxDSAction& GetCurrentAction() { return m_action; }
	LegoCharacterManager* GetCharacterManager() { return m_characterManager; }
	LegoWorldList* GetWorldList() { return m_worldList; }

	void SetNavController(LegoNavController* p_navController) {
		m_navController = p_navController;
	}
	void SetUserActor(LegoPathActor* p_userActor) { m_userActor = p_userActor; }
	void SetCurrentWorld(LegoWorld* p_currentWorld) {
		m_currentWorld = p_currentWorld;
	}

	void SetExit(MxBool p_exit) { m_exit = p_exit; }

	MxResult StartActionIfUnknown0x13c(MxDSAction& p_dsAction) {
		return m_unk0x13c ? Start(&p_dsAction) : SUCCESS;
	}
	void SetUnknown13c(MxBool p_unk0x13c) { m_unk0x13c = p_unk0x13c; }

	void CloseMainWindow() { PostMessageA(m_windowHandle, WM_CLOSE, 0, 0); }

	// LegoOmni::`scalar deleting destructor'

private:
	WorldContainer* m_worlds;
	ViewLODListManager* m_viewLODListManager;
	LegoInputManager* m_inputManager;
	LegoTextureContainer* m_textureContainer;
	LegoWorldList* m_worldList;
	LegoWorld* m_currentWorld;
	MxBool m_exit;
	LegoNavController* m_navController;
	LegoPathActor* m_userActor;
	LegoCharacterManager* m_characterManager;
	LegoPlantManager* m_plantManager;
	LegoAnimationManager* m_animationManager;
	LegoBuildingManager* m_buildingManager;
	LegoGameState* m_gameState;
	MxDSAction m_action;
	MxBackgroundAudioManager* m_bkgAudioManager;
	MxTransitionManager* m_transitionManager;

public:
	MxBool m_unk0x13c;
};

