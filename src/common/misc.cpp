#include "misc.h"

#include "3dmanager/lego3dmanager.h"
#include "legoinputmanager.h"
#include "legomain.h"
#include "legovideomanager.h"
#include "mxbackgroundaudiomanager.h"
#include "mxmisc.h"
#include "roi/legoroi.h"
#include "scripts.h"

MxBool g_isWorldActive = TRUE;

LegoOmni* Lego() {
	return LegoOmni::GetInstance();
}

LegoSoundManager* SoundManager() {
	return LegoOmni::GetInstance()->GetSoundManager();
}

LegoVideoManager* VideoManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetVideoManager();
}

MxBackgroundAudioManager* BackgroundAudioManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetBackgroundAudioManager();
}

LegoInputManager* InputManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetInputManager();
}

LegoControlManager* ControlManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetInputManager()->GetControlManager();
}

LegoGameState* GameState() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetGameState();
}

LegoAnimationManager* AnimationManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetAnimationManager();
}

LegoNavController* NavController() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetNavController();
}

LegoPathActor* UserActor() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetUserActor();
}

LegoWorld* CurrentWorld() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetCurrentWorld();
}

LegoCharacterManager* CharacterManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetCharacterManager();
}

ViewManager* GetViewManager() {
	return VideoManager()->Get3DManager()->GetLego3DView()->GetViewManager();
}

LegoPlantManager* PlantManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetPlantManager();
}

LegoBuildingManager* BuildingManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetBuildingManager();
}

LegoTextureContainer* TextureContainer() {
	return LegoOmni::GetInstance()->GetTextureContainer();
}

ViewLODListManager* GetViewLODListManager() {
	return LegoOmni::GetInstance()->GetViewLODListManager();
}

void FUN_10015820(MxBool p_disable, MxU16 p_flags) {
	assert(LegoOmni::GetInstance());
	LegoOmni::GetInstance()->FUN_1005b4f0(p_disable, p_flags);
}

LegoROI* FindROI(const char* p_name) {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->FindROI(p_name);
}

void SetROIVisible(const char* p_name, MxBool p_visible) {
	LegoROI* roi = FindROI(p_name);

	if (roi) {
		roi->SetVisibility(p_visible);
	}
}

void SetUserActor(LegoPathActor* p_userActor) {
	LegoOmni::GetInstance()->SetUserActor(p_userActor);
}

MxResult StartActionIfUnknown0x13c(MxDSAction& p_dsAction) {
	return LegoOmni::GetInstance()->StartActionIfUnknown0x13c(p_dsAction);
}

void DeleteAction() {
	LegoOmni::GetInstance()->DeleteAction();
}

LegoWorld* FindWorld(const MxAtomId& p_atom, MxS32 p_entityid) {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->FindWorld(p_atom, p_entityid);
}

MxDSAction& GetCurrentAction() {
	return LegoOmni::GetInstance()->GetCurrentAction();
}

void SetCurrentWorld(LegoWorld* p_world) {
	LegoOmni::GetInstance()->SetCurrentWorld(p_world);
}

MxTransitionManager* TransitionManager() {
	assert(LegoOmni::GetInstance());
	return LegoOmni::GetInstance()->GetTransitionManager();
}

void PlayMusic(JukeboxScript::Script p_objectId) {
	assert(LegoOmni::GetInstance());

	MxDSAction action;
	action.SetAtomId(*g_jukeboxScript);
	action.SetObjectId(p_objectId);

	LegoOmni::GetInstance()->GetBackgroundAudioManager()->PlayMusic(
		action,
		5,
		MxPresenter::e_repeating
	);
}

void SetIsWorldActive(MxBool p_isWorldActive) {
	if (!p_isWorldActive) {
		LegoOmni::GetInstance()->GetInputManager()->SetCamera(NULL);
	}
	g_isWorldActive = p_isWorldActive;
}

void DeleteObjects(MxAtomId* p_id, MxS32 p_first, MxS32 p_last) {
	MxDSAction action;

	action.SetAtomId(*p_id);
	action.SetUnknown24(-2);

	for (MxS32 first = p_first, last = p_last; first <= last; first++) {
		action.SetObjectId(first);
		DeleteObject(action);
	}
}
