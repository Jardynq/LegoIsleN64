#include "world_presenter.h"

#include "define.h"
#include "actor_presenter.h"
#include "animation_manager.h"
#include "building_manager.h"
#include "entity.h"
#include "legomain.h"
#include "model_presenter.h"
#include "part_presenter.h"
#include "plant_manager.h"
#include "texture_presenter.h"
#include "video_manager.h"
#include "world.h"
#include "misc.h"
#include "modeldb.h"
#include "mx_action_notification_param.h"
#include "mxautolock.h"
#include "mx_ds_action_list.h"
#include "mx_ds_chunk.h"
#include "mx_ds_media_action.h"
#include "mx_ds_multi_action.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_object_factory.h"
#include "mx_presenter.h"
#include "mx_utilities.h"

#include <io.h>

MxS32 g_legoWorldPresenterQuality = 1;

MxLong g_wdbOffset = 0;

void LegoWorldPresenter::configureLegoWorldPresenter(
	MxS32 p_legoWorldPresenterQuality
) {
	g_legoWorldPresenterQuality = p_legoWorldPresenterQuality;
}

LegoWorldPresenter::LegoWorldPresenter() {
	m_unk0x50 = 50000;
}

LegoWorldPresenter::~LegoWorldPresenter() {
	MxBool result = FALSE;
	if (m_entity) {
		LegoOmni::World worldId = ((LegoWorld*) m_entity)->GetWorldId();
		PlantManager()->LoadWorldInfo(worldId);
		AnimationManager()->LoadWorldInfo(worldId);
		BuildingManager()->LoadWorldInfo();
		result = ((LegoWorld*) m_entity)->VTable0x5c();
	}

	if (result == FALSE) {
		FUN_10015820(
			FALSE,
			LegoOmni::c_disableInput | LegoOmni::c_disable3d |
				LegoOmni::c_clearScreen
		);
	}

	if (m_entity) {
		NotificationManager()->Send(
			m_entity,
			MxNotificationParam(c_notificationNewPresenter, NULL)
		);
	}
}

MxResult LegoWorldPresenter::StartAction(
	MxStreamController* p_controller,
	MxDSAction* p_action
) {
	AUTOLOCK(m_criticalSection);

	MxResult result = FAILURE;
	MxDSActionList* actions = ((MxDSMultiAction*) p_action)->GetActionList();
	MxObjectFactory* factory = ObjectFactory();
	MxDSActionListCursor cursor(actions);
	MxDSAction* action;

	if (MxPresenter::StartAction(p_controller, p_action) == SUCCESS) {
		cursor.Head();

		while (cursor.Current(action)) {
			MxBool success = FALSE;
			const char* presenterName;
			MxPresenter* presenter = NULL;

			cursor.Next();

			if (m_action->GetFlags() & MxDSAction::c_looping) {
				action->SetFlags(action->GetFlags() | MxDSAction::c_looping);
			} else if (m_action->GetFlags() & MxDSAction::c_bit3) {
				action->SetFlags(action->GetFlags() | MxDSAction::c_bit3);
			}

			presenterName = PresenterNameDispatch(*action);
			presenter = (MxPresenter*) factory->Create(presenterName);

			if (presenter && presenter->AddToManager() == SUCCESS) {
				presenter->SetCompositePresenter(this);
				if (presenter->StartAction(p_controller, action) == SUCCESS) {
					presenter->SetTickleState(e_idle);
					success = TRUE;
				}
			}

			if (success) {
				action->SetOrigin(this);
				m_list.push_back(presenter);
			} else if (presenter) {
				delete presenter;
			}
		}

		VideoManager()->RegisterPresenter(*this);

		result = SUCCESS;
	}

	return result;
}

void LegoWorldPresenter::ReadyTickle() {
	m_entity = (LegoEntity*) MxPresenter::CreateEntity("LegoWorld");
	if (m_entity) {
		m_entity->Create(*m_action);
		Lego()->AddWorld((LegoWorld*) m_entity);
		SetEntityLocation(
			m_action->GetLocation(),
			m_action->GetDirection(),
			m_action->GetUp()
		);
	}

	ParseExtra();
	ProgressTickleState(e_starting);
}

void LegoWorldPresenter::StartingTickle() {
	if (m_action->IsA("MxDSSerialAction")) {
		MxPresenter* presenter = *m_list.begin();
		if (presenter->GetCurrentTickleState() == e_idle) {
			presenter->SetTickleState(e_ready);
		}
	} else {
		for (MxCompositePresenterList::iterator it = m_list.begin();
			 it != m_list.end();
			 it++) {
			if ((*it)->GetCurrentTickleState() == e_idle) {
				(*it)->SetTickleState(e_ready);
			}
		}
	}

	ProgressTickleState(e_streaming);
}

MxResult LegoWorldPresenter::LoadWorld(char* p_worldName, LegoWorld* p_world) {
	ModelDbWorld* worlds = NULL;
	MxS32 numWorlds = 0, i = 0, j = 0;
	MxU32 size = 0;
	MxU8* buff = nullptr;
	FILE* wdbFile = asset_fopen("rom:/data/world.wdb", nullptr);

	if (wdbFile == NULL) {
		return FAILURE;
	}

	ReadModelDbWorlds(wdbFile, worlds, numWorlds);

	for (i = 0; i < numWorlds; i++) {
		if (!strcmpi(worlds[i].m_worldName, p_worldName)) {
			break;
		}
	}

	if (i == numWorlds) {
		return FAILURE;
	}

	if (g_wdbOffset == 0) {
		if (fread(&size, sizeof(size), 1, wdbFile) != 1) {
			return FAILURE;
		}

		buff = new MxU8[size];
		if (fread(buff, size, 1, wdbFile) != 1) {
			return FAILURE;
		}

		MxDSChunk chunk;
		chunk.SetLength(size);
		chunk.SetData(buff);

		LegoTexturePresenter texturePresenter;
		if (texturePresenter.Read(chunk) == SUCCESS) {
			texturePresenter.Store();
		}

		delete[] buff;

		if (fread(&size, sizeof(size), 1, wdbFile) != 1) {
			return FAILURE;
		}

		buff = new MxU8[size];
		if (fread(buff, size, 1, wdbFile) != 1) {
			return FAILURE;
		}

		chunk.SetLength(size);
		chunk.SetData(buff);

		LegoPartPresenter partPresenter;
		if (partPresenter.Read(chunk) == SUCCESS) {
			partPresenter.Store();
		}

		delete[] buff;

		g_wdbOffset = ftell(wdbFile);
	} else {
		if (fseek(wdbFile, g_wdbOffset, SEEK_SET) != 0) {
			return FAILURE;
		}
	}

	ModelDbPartListCursor cursor(worlds[i].m_partList);
	ModelDbPart* part;

	while (cursor.Next(part)) {
		if (GetViewLODListManager()->Lookup(part->m_roiName.GetData()) ==
				NULL &&
			FUN_10067360(*part, wdbFile) != SUCCESS) {
			return FAILURE;
		}
	}

	for (j = 0; j < worlds[i].m_numModels; j++) {
		if (!strnicmp(worlds[i].m_models[j].m_modelName, "isle", 4)) {
			switch (g_legoWorldPresenterQuality) {
			case 0:
				if (strcmpi(worlds[i].m_models[j].m_modelName, "isle_lo")) {
					continue;
				}
				break;
			case 1:
				if (strcmpi(worlds[i].m_models[j].m_modelName, "isle")) {
					continue;
				}
				break;
			case 2:
				if (strcmpi(worlds[i].m_models[j].m_modelName, "isle_hi")) {
					continue;
				}
			}
		} else if (g_legoWorldPresenterQuality <= 1 &&
				   !strnicmp(worlds[i].m_models[j].m_modelName, "haus", 4)) {
			if (worlds[i].m_models[j].m_modelName[4] == '3') {
				if (FUN_100674b0(worlds[i].m_models[j], wdbFile, p_world) !=
					SUCCESS) {
					return FAILURE;
				}

				if (FUN_100674b0(worlds[i].m_models[j - 2], wdbFile, p_world) !=
					SUCCESS) {
					return FAILURE;
				}

				if (FUN_100674b0(worlds[i].m_models[j - 1], wdbFile, p_world) !=
					SUCCESS) {
					return FAILURE;
				}
			}

			continue;
		}

		if (FUN_100674b0(worlds[i].m_models[j], wdbFile, p_world) != SUCCESS) {
			return FAILURE;
		}
	}

	FreeModelDbWorlds(worlds, numWorlds);
	fclose(wdbFile);
	return SUCCESS;
}

MxResult
LegoWorldPresenter::FUN_10067360(ModelDbPart& p_part, FILE* p_wdbFile) {
	MxResult result;
	MxU8* buff = new MxU8[p_part.m_partDataLength];

	fseek(p_wdbFile, p_part.m_partDataOffset, SEEK_SET);
	if (fread(buff, p_part.m_partDataLength, 1, p_wdbFile) != 1) {
		return FAILURE;
	}

	MxDSChunk chunk;
	chunk.SetLength(p_part.m_partDataLength);
	chunk.SetData(buff);

	LegoPartPresenter partPresenter;
	result = partPresenter.Read(chunk);

	if (result == SUCCESS) {
		partPresenter.Store();
	}

	delete[] buff;
	return result;
}

MxResult LegoWorldPresenter::FUN_100674b0(
	ModelDbModel& p_model,
	FILE* p_wdbFile,
	LegoWorld* p_world
) {
	MxU8* buff = new MxU8[p_model.m_unk0x04];

	fseek(p_wdbFile, p_model.m_unk0x08, SEEK_SET);
	if (fread(buff, p_model.m_unk0x04, 1, p_wdbFile) != 1) {
		return FAILURE;
	}

	MxDSChunk chunk;
	chunk.SetLength(p_model.m_unk0x04);
	chunk.SetData(buff);

	MxDSAction action;
	MxAtomId atom;
	action.SetLocation(p_model.m_location);
	action.SetDirection(p_model.m_direction);
	action.SetUp(p_model.m_up);

	MxU32 objectId = m_unk0x50;
	m_unk0x50++;
	action.SetObjectId(objectId);

	action.SetAtomId(atom);

	LegoEntity* createdEntity = NULL;

	if (!strcmp(p_model.m_presenterName, "LegoActorPresenter")) {
		LegoActorPresenter presenter;
		presenter.SetAction(&action);
		LegoEntity* entity = (LegoEntity*) presenter.CreateEntity("LegoActor");
		presenter.SetInternalEntity(entity);
		presenter.SetEntityLocation(
			p_model.m_location,
			p_model.m_direction,
			p_model.m_up
		);
		entity->Create(action);
	} else if (!strcmp(p_model.m_presenterName, "LegoEntityPresenter")) {
		LegoEntityPresenter presenter;
		presenter.SetAction(&action);
		createdEntity = (LegoEntity*) presenter.CreateEntity("LegoEntity");
		presenter.SetInternalEntity(createdEntity);
		presenter.SetEntityLocation(
			p_model.m_location,
			p_model.m_direction,
			p_model.m_up
		);
		createdEntity->Create(action);
	}

	LegoModelPresenter modelPresenter;

	if (createdEntity != NULL) {
		action.SetLocation(Mx3DPointFloat(0.0, 0.0, 0.0));
		action.SetUp(Mx3DPointFloat(0.0, 0.0, 1.0));
		action.SetDirection(Mx3DPointFloat(0.0, 1.0, 0.0));
	}

	modelPresenter.SetAction(&action);
	modelPresenter
		.FUN_1007ff70(chunk, createdEntity, p_model.m_unk0x34, p_world);
	delete[] buff;

	return SUCCESS;
}

void LegoWorldPresenter::VTable0x60(MxPresenter* p_presenter) {
	MxCompositePresenter::VTable0x60(p_presenter);
	MxDSAction* action = p_presenter->GetAction();

	if (action->GetDuration() != -1 &&
		(action->GetFlags() & MxDSAction::c_looping) == 0) {
		if (!action->IsA("MxDSMediaAction")) {
			return;
		}

		if (((MxDSMediaAction*) action)->GetSustainTime() != -1) {
			return;
		}
	}

	if (!p_presenter->IsA("LegoAnimPresenter") &&
		!p_presenter->IsA("MxControlPresenter") &&
		!p_presenter->IsA("MxCompositePresenter")) {
		p_presenter->SendToCompositePresenter(Lego());
		((LegoWorld*) m_entity)->Add(p_presenter);
	}
}

void LegoWorldPresenter::ParseExtra() {
	MxU16 extraLength;
	char* extraData;
	m_action->GetExtra(extraLength, extraData);

	if (extraLength) {
		char extraCopy[1024];
		memcpy(extraCopy, extraData, extraLength);
		extraCopy[extraLength] = '\0';

		char output[1024];
		if (KeyValueStringParse(output, g_strWORLD, extraCopy)) {
			char* worldKey = strtok(output, g_parseExtraTokens);
			LoadWorld(worldKey, (LegoWorld*) m_entity);
			((LegoWorld*) m_entity)->SetWorldId(Lego()->GetWorldId(worldKey));
		}
	}
}
