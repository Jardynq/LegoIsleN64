#include "anim_presenter.h"

#include "3d_manager.h"
#include "anim.h"
#include "define.h"
#include "animation_manager.h"
#include "anim_mm_presenter.h"
#include "camera_controller.h"
#include "character_manager.h"
#include "end_anim_notification_param.h"
#include "path_boundary.h"
#include "video_manager.h"
#include "world.h"
#include "misc.h"
#include "mxautolock.h"
#include "mx_composite_presenter.h"
#include "mx_ds_anim.h"
#include "mx_ds_subscriber.h"
#include "mx_misc.h"
#include "mx_notification_manager.h"
#include "mx_stream_chunk.h"
#include "mx_timer.h"
#include "mx_utilities.h"
#include "mx_variable_table.h"
#include "mx_video_manager.h"
#include "realtime.h"
#include "view_manager.h"

LegoAnimPresenter::LegoAnimPresenter() {
	Init();
}

LegoAnimPresenter::~LegoAnimPresenter() {
	Destroy(TRUE);
}

void LegoAnimPresenter::Init() {
	m_anim = NULL;
	m_roiMap = NULL;
	m_roiMapSize = 0;
	m_unk0x74 = NULL;
	m_unk0x70 = NULL;
	m_unk0x78 = NULL;
	m_flags = 0;
	m_unk0xa8.Clear();
	m_unk0xa4 = 0;
	m_currentWorld = NULL;
	m_unk0x95 = FALSE;
	m_worldId = -1;
	m_substMap = NULL;
	m_worldAtom.Clear();
	m_unk0x9c = 0;
	m_unk0x8c = NULL;
	m_unk0x90 = NULL;
	m_unk0x94 = 0;
	m_unk0x96 = TRUE;
	m_unk0xa0 = NULL;
}

void LegoAnimPresenter::Destroy(MxBool p_fromDestructor) {
	{
		AUTOLOCK(m_criticalSection);

		if (m_anim != NULL) {
			delete m_anim;
		}

		if (m_roiMap != NULL) {
			delete[] m_roiMap;
		}

		if (m_unk0x70 != NULL) {
			delete m_unk0x70;
		}

		if (m_unk0x74 != NULL) {
			FUN_1006aa60();
			delete m_unk0x74;
		}

		if (m_unk0x78 != NULL) {
			delete m_unk0x78;
		}

		if (m_substMap != NULL) {
			MxVariableTable* variableTable = VariableTable();

			for (LegoAnimSubstMap::iterator it = m_substMap->begin();
				 it != m_substMap->end();
				 it++) {
				variableTable->SetVariable((*it).first, "");

				delete[] const_cast<char*>((*it).first);
				delete[] const_cast<char*>((*it).second);
			}

			delete m_substMap;
		}

		if (m_unk0x90 != NULL) {
			for (MxS32 i = 0; i < m_unk0x94; i++) {
				if (m_unk0x90[i] != NULL) {
					delete[] m_unk0x90[i];
				}
			}

			delete[] m_unk0x90;
		}

		if (m_unk0x8c != NULL) {
			delete[] m_unk0x8c;
		}

		if (m_unk0xa0 != NULL) {
			delete m_unk0xa0;
		}

		Init();
	}

	if (!p_fromDestructor) {
		MxVideoPresenter::Destroy(FALSE);
	}
}

MxResult LegoAnimPresenter::CreateAnim(MxStreamChunk* p_chunk) {
	MxResult result = FAILURE;
	LegoMemory storage(p_chunk->GetData());
	MxS32 magicSig;
	LegoS32 parseScene = 0;
	MxS32 val3;

	if (storage.Read(&magicSig, sizeof(magicSig)) != SUCCESS ||
		magicSig != 0x11) {
		goto done;
	}
	if (storage.Read(&m_unk0xa4, sizeof(m_unk0xa4)) != SUCCESS) {
		goto done;
	}
	if (storage.Read(&m_unk0xa8[0], sizeof(m_unk0xa8[0])) != SUCCESS) {
		goto done;
	}
	if (storage.Read(&m_unk0xa8[1], sizeof(m_unk0xa8[1])) != SUCCESS) {
		goto done;
	}
	if (storage.Read(&m_unk0xa8[2], sizeof(m_unk0xa8[2])) != SUCCESS) {
		goto done;
	}
	if (storage.Read(&parseScene, sizeof(parseScene)) != SUCCESS) {
		goto done;
	}
	if (storage.Read(&val3, sizeof(val3)) != SUCCESS) {
		goto done;
	}

	m_anim = new LegoAnim();
	if (!m_anim) {
		goto done;
	}

	if (m_anim->Read(&storage, parseScene) != SUCCESS) {
		goto done;
	}

	result = SUCCESS;

done:
	if (result != SUCCESS) {
		delete m_anim;
		Init();
	}

	return result;
}

LegoChar* LegoAnimPresenter::FUN_10069150(const LegoChar* p_und1) {
	LegoChar* str;

	if (LegoCharacterManager::IsActor(p_und1 + 1)) {
		str = new LegoChar[strlen(p_und1)];

		if (str != NULL) {
			strcpy(str, p_und1 + 1);
		}
	} else {
		LegoChar buffer[32];
		sprintf(buffer, "%d", m_action->GetUnknown24());
		str = new LegoChar
			[strlen(p_und1) + strlen(buffer) + strlen(GetActionObjectName()) +
			 1];

		if (str != NULL) {
			strcpy(str, p_und1);
			strcat(str, buffer);
			strcat(str, GetActionObjectName());
		}
	}

	return str;
}

void LegoAnimPresenter::FUN_100692b0() {
	m_unk0x74 = new LegoROIList();

	if (m_unk0x74) {
		LegoU32 numActors = m_anim->GetNumActors();

		for (LegoU32 i = 0; i < numActors; i++) {
			LegoChar* str = FUN_100697c0(m_anim->GetActorName(i), NULL);
			undefined4 unk0x04 = m_anim->GetActorUnknown0x04(i);
			LegoROI* roi = NULL;

			if (unk0x04 == 2) {
				LegoChar* src;
				if (str[0] == '*') {
					src = str + 1;
				} else {
					src = str;
				}

				roi = CharacterManager()->GetActorROI(src, TRUE);

				if (roi != NULL && str[0] == '*') {
					roi->SetVisibility(FALSE);
				}
			} else if (unk0x04 == 4) {
				LegoChar* baseName = new LegoChar[strlen(str)];
				strcpy(baseName, str + 1);
				strlwr(baseName);

				LegoChar* und = FUN_10069150(str);
				roi = CharacterManager()->FUN_10085a80(und, baseName, TRUE);

				if (roi != NULL) {
					roi->SetVisibility(FALSE);
				}

				delete[] baseName;
				delete[] und;
			} else if (unk0x04 == 3) {
				LegoChar* lodName = new LegoChar[strlen(str)];
				strcpy(lodName, str + 1);

				for (LegoChar* i = &lodName[strlen(lodName) - 1]; i > lodName;
					 i--) {
					if ((*i < '0' || *i > '9') && *i != '_') {
						break;
					}

					*i = '\0';
				}

				strlwr(lodName);

				LegoChar* und = FUN_10069150(str);
				roi = CharacterManager()->CreateAutoROI(und, lodName, TRUE);

				if (roi != NULL) {
					roi->SetVisibility(FALSE);
				}

				delete[] lodName;
				delete[] und;
			}

			if (roi != NULL) {
				m_unk0x74->Append(roi);
			}

			delete[] str;
		}
	}
}

void LegoAnimPresenter::FUN_100695c0() {
	m_unk0x70 = new LegoROIList();

	if (m_unk0x70) {
		const CompoundObject& rois = VideoManager()
										 ->Get3DManager()
										 ->GetLego3DView()
										 ->GetViewManager()
										 ->GetROIs();
		LegoU32 numActors = m_anim->GetNumActors();

		for (LegoU32 i = 0; i < numActors; i++) {
			if (FUN_100698b0(rois, m_anim->GetActorName(i)) == FALSE) {
				undefined4 unk0x04 = m_anim->GetActorUnknown0x04(i);

				if (unk0x04 == 5 || unk0x04 == 6) {
					LegoChar lodName[256];
					const LegoChar* actorName = m_anim->GetActorName(i);

					LegoU32 len = strlen(actorName);
					strcpy(lodName, actorName);

					for (LegoChar* i = &lodName[len - 1];
						 isdigit(*i) || *i == '_';
						 i--) {
						*i = '\0';
					}

					strlwr(lodName);

					CharacterManager()
						->CreateAutoROI(actorName, lodName, FALSE);
					FUN_100698b0(rois, actorName);
				}
			}
		}
	}
}

LegoChar* LegoAnimPresenter::FUN_100697c0(
	const LegoChar* p_und1,
	const LegoChar* p_und2
) {
	const LegoChar* str = p_und1;
	const char* var = VariableTable()->GetVariable(p_und1);

	if (*var) {
		str = var;
	}

	LegoU32 len = strlen(str) + (p_und2 ? strlen(p_und2) : 0) + 2;
	LegoChar* result = new LegoChar[len];

	if (result != NULL) {
		*result = '\0';

		if (p_und2) {
			strcpy(result, p_und2);
			strcat(result, ":");
		}

		strcat(result, str);
	}

	return result;
}

LegoBool LegoAnimPresenter::FUN_100698b0(
	const CompoundObject& p_rois,
	const LegoChar* p_und2
) {
	LegoBool result = FALSE;

	LegoChar* str;
	if (*(str = FUN_100697c0(p_und2, NULL)) == '*') {
		LegoChar* tmp = FUN_10069150(str);
		delete[] str;
		str = tmp;
	}

	if (str != NULL && *str != '\0' && p_rois.size() > 0) {
		for (CompoundObject::const_iterator it = p_rois.begin();
			 it != p_rois.end();
			 it++) {
			LegoROI* roi = (LegoROI*) *it;
			const char* name = roi->GetName();

			if (name != NULL) {
				if (!strcmpi(name, str)) {
					m_unk0x70->Append(roi);
					result = TRUE;
					break;
				}
			}
		}
	}

	delete[] str;
	return result;
}

LegoROI* LegoAnimPresenter::FUN_100699e0(const LegoChar* p_und) {
	LegoROIListCursor cursor(m_unk0x70);
	LegoROI* roi;

	while (cursor.Next(roi)) {
		LegoChar* und = FUN_100697c0(roi->GetName(), NULL);

		if (und != NULL && !strcmpi(und, p_und)) {
			delete[] und;
			return roi;
		}

		delete[] und;
	}

	return NULL;
}

void LegoAnimPresenter::FUN_10069b10() {
	LegoAnimStructMap anims;

	if (m_unk0x8c != NULL) {
		memset(m_unk0x8c, 0, m_unk0x94 * sizeof(*m_unk0x8c));
	}

	FUN_1006a3c0(anims, m_anim->GetRoot(), NULL);

	if (m_roiMap != NULL) {
		delete[] m_roiMap;
		m_roiMapSize = 0;
	}

	m_roiMapSize = 0;
	m_roiMap = new LegoROI*[anims.size() + 1];
	memset(m_roiMap, 0, (anims.size() + 1) * sizeof(*m_roiMap));

	for (LegoAnimStructMap::iterator it = anims.begin(); it != anims.end();) {
		MxU32 index = (*it).second.m_index;
		m_roiMap[index] = (*it).second.m_roi;

		if (m_roiMap[index]->GetName() != NULL) {
			for (MxS32 i = 0; i < m_unk0x94; i++) {
				if (m_unk0x8c[i] == NULL && m_unk0x90[i] != NULL) {
					if (!strcmpi(m_unk0x90[i], m_roiMap[index]->GetName())) {
						m_unk0x8c[i] = m_roiMap[index];
						break;
					}
				}
			}
		}

		delete[] const_cast<char*>((*it).first);
		it++;
		m_roiMapSize++;
	}
}

void LegoAnimPresenter::FUN_1006a3c0(
	LegoAnimStructMap& p_map,
	LegoTreeNode* p_node,
	LegoROI* p_roi
) {
	LegoROI* roi = p_roi;
	LegoChar* und = NULL;
	LegoChar* und2 = NULL;
	LegoAnimNodeData* data = (LegoAnimNodeData*) p_node->GetData();
	const LegoChar* name = data->GetName();

	if (name != NULL && *name != '-') {
		if (*name == '*') {
			name = und2 = FUN_10069150(name);
		}

		und = FUN_100697c0(name, p_roi != NULL ? p_roi->GetName() : NULL);

		if (p_roi == NULL) {
			roi = FUN_100699e0(und);

			if (roi != NULL) {
				FUN_1006a4f0(p_map, data, und, roi);
			} else {
				data->SetUnknown0x20(0);
			}
		} else {
			LegoROI* child = p_roi->FindChildROI(name, p_roi);

			if (child != NULL) {
				FUN_1006a4f0(p_map, data, und, child);
			} else {
				if (FUN_100699e0(name) != NULL) {
					FUN_1006a3c0(p_map, p_node, NULL);
					delete[] und;
					delete[] und2;
					return;
				}
			}
		}
	}

	delete[] und;
	delete[] und2;

	MxS32 count = p_node->GetNumChildren();
	for (MxS32 i = 0; i < count; i++) {
		FUN_1006a3c0(p_map, p_node->GetChild(i), roi);
	}
}

void LegoAnimPresenter::FUN_1006a4f0(
	LegoAnimStructMap& p_map,
	LegoAnimNodeData* p_data,
	const LegoChar* p_und,
	LegoROI* p_roi
) {
	LegoAnimStructMap::iterator it;

	it = p_map.find(p_und);
	if (it == p_map.end()) {
		LegoAnimStruct animStruct;
		animStruct.m_index = p_map.size() + 1;
		animStruct.m_roi = p_roi;

		p_data->SetUnknown0x20(animStruct.m_index);

		LegoChar* und = new LegoChar[strlen(p_und) + 1];
		strcpy(und, p_und);

		p_map[und] = animStruct;
	} else {
		p_data->SetUnknown0x20((*it).second.m_index);
	}
}

void LegoAnimPresenter::FUN_1006aa60() {
	LegoROIListCursor cursor(m_unk0x74);
	LegoROI* roi;

	while (cursor.Next(roi)) {
		const char* name = roi->GetName();

		if (m_unk0x96 || !CharacterManager()->IsActor(name)) {
			CharacterManager()->ReleaseActor(name);
		}
	}
}

void LegoAnimPresenter::FUN_1006ab70() {
	if (m_unk0x96) {
		AnimationManager()->FUN_10063270(m_unk0x74, this);
	} else {
		AnimationManager()->FUN_10063780(m_unk0x74);
	}
}

LegoBool LegoAnimPresenter::FUN_1006aba0() {
	return FUN_1006abb0(m_anim->GetRoot(), 0);
}

MxBool LegoAnimPresenter::FUN_1006abb0(LegoTreeNode* p_node, LegoROI* p_roi) {
	MxBool result = FALSE;
	LegoROI* roi = p_roi;
	LegoChar* und = NULL;
	const LegoChar* name = ((LegoAnimNodeData*) p_node->GetData())->GetName();
	MxS32 i, count;

	if (name != NULL && *name != '-') {
		und = FUN_100697c0(name, p_roi != NULL ? p_roi->GetName() : NULL);

		if (p_roi == NULL) {
			roi = FUN_100699e0(und);

			if (roi == NULL) {
				goto done;
			}
		} else {
			LegoROI* child = p_roi->FindChildROI(name, p_roi);

			if (child == NULL) {
				if (FUN_100699e0(name) != NULL) {
					if (FUN_1006abb0(p_node, NULL)) {
						result = TRUE;
					}
				}

				goto done;
			}
		}
	}

	count = p_node->GetNumChildren();
	for (i = 0; i < count; i++) {
		if (!FUN_1006abb0(p_node->GetChild(i), roi)) {
			goto done;
		}
	}

	result = TRUE;

done:
	if (und != NULL) {
		delete[] und;
	}

	return result;
}

void LegoAnimPresenter::SubstituteVariables() {
	if (m_substMap != NULL) {
		MxVariableTable* variableTable = VariableTable();

		for (LegoAnimSubstMap::iterator it = m_substMap->begin();
			 it != m_substMap->end();
			 it++) {
			variableTable->SetVariable((*it).first, (*it).second);
		}
	}
}

void LegoAnimPresenter::PutFrame() {
	if (m_currentTickleState == e_streaming) {
		MxLong time;

		if (m_action->GetStartTime() <= m_action->GetElapsedTime()) {
			time = m_action->GetElapsedTime() - m_action->GetStartTime();
		} else {
			time = 0;
		}

		FUN_1006b9a0(m_anim, time, m_unk0x78);

		if (m_unk0x8c != NULL && m_currentWorld != NULL &&
			m_currentWorld->GetCameraController() != NULL) {
			for (MxS32 i = 0; i < m_unk0x94; i++) {
				if (m_unk0x8c[i] != NULL) {
					MxMatrix mat(m_unk0x8c[i]->GetLocal2World());

					Vector3 pos(mat[0]);
					Vector3 dir(mat[1]);
					Vector3 up(mat[2]);
					Vector3 und(mat[3]);

					float possqr = sqrt(pos.LenSquared());
					float dirsqr = sqrt(dir.LenSquared());
					float upsqr = sqrt(up.LenSquared());

					up = und;

					up -=
						m_currentWorld->GetCameraController()->GetWorldLocation(
						);
					dir /= dirsqr;
					pos.EqualsCross(dir, up);
					pos.Unitize();
					up.EqualsCross(pos, dir);
					pos *= possqr;
					dir *= dirsqr;
					up *= upsqr;

					m_unk0x8c[i]->FUN_100a58f0(mat);
					m_unk0x8c[i]->VTable0x14();
				}
			}
		}
	}
}

MxResult LegoAnimPresenter::FUN_1006afc0(MxMatrix*& p_matrix, float p_und) {
	MxU32 length = m_roiMapSize + 1;
	p_matrix = new MxMatrix[length];

	MxS32 i;
	for (i = 1; i < length; i++) {
		if (m_roiMap[i] != NULL) {
			p_matrix[i] = m_roiMap[i]->GetLocal2World();
		}
	}

	FUN_1006b900(m_anim, p_und, m_unk0x78);

	for (i = 1; i < length; i++) {
		MxMatrix mat;

		if (m_roiMap[i] != NULL) {
			mat = p_matrix[i];
			p_matrix[i] = m_roiMap[i]->GetLocal2World();
			m_roiMap[i]->FUN_100a58f0(mat);
		}
	}

	return SUCCESS;
}

MxResult LegoAnimPresenter::FUN_1006b140(LegoROI* p_roi) {
	if (p_roi == NULL) {
		return FAILURE;
	}

	MxMatrix* mn = new MxMatrix();
	MxMatrix local58;
	const Matrix4& local2world = p_roi->GetLocal2World();
	MxMatrix* local5c;
	MxU32 i;

	if (FUN_1006afc0(local5c, 0.0f) != SUCCESS) {
		goto done;
	}

	for (i = 1; i <= m_roiMapSize; i++) {
		if (m_roiMap[i] == p_roi) {
			if (local5c[i].BETA_1005a590(local58) != SUCCESS) {
				goto done;
			}

			break;
		}
	}

	{
		((Matrix4*) mn)->Product(local58, local2world);
		SetUnknown0xa0(mn);
		delete[] local5c;
		SetUnknown0x0cTo1();

		MxMatrix local140(*m_unk0x78);
		MxMatrix localf8;

		localf8.Product(local140, *m_unk0xa0);
		((Matrix4&) *m_unk0x78) = localf8;
		return SUCCESS;
	}

done:
	if (mn != NULL) {
		delete mn;
	}

	if (local5c != NULL) {
		delete[] local5c;
	}

	return FAILURE;
}

void LegoAnimPresenter::ReadyTickle() {
	m_currentWorld = CurrentWorld();

	if (m_currentWorld) {
		MxStreamChunk* chunk = m_subscriber->PeekData();

		if (chunk && chunk->GetTime() + m_action->GetStartTime() <=
						 m_action->GetElapsedTime()) {
			chunk = m_subscriber->PopData();
			MxResult result = CreateAnim(chunk);
			m_subscriber->FreeDataChunk(chunk);

			if (result == SUCCESS) {
				ProgressTickleState(e_starting);
				ParseExtra();
			} else {
				EndAction();
			}
		}
	}
}

void LegoAnimPresenter::StartingTickle() {
	SubstituteVariables();
	FUN_100692b0();
	FUN_100695c0();

	if (m_flags & c_mustSucceed && !FUN_1006aba0()) {
		goto done;
	}

	FUN_10069b10();
	FUN_1006c8a0(TRUE);

	if (m_unk0x78 == NULL) {
		if (fabs(m_action->GetDirection()[0]) >= 0.00000047683716F ||
			fabs(m_action->GetDirection()[1]) >= 0.00000047683716F ||
			fabs(m_action->GetDirection()[2]) >= 0.00000047683716F) {
			m_unk0x78 = new MxMatrix();
			CalcLocalTransform(
				m_action->GetLocation(),
				m_action->GetDirection(),
				m_action->GetUp(),
				*m_unk0x78
			);
		} else if (m_roiMap != NULL) {
			LegoROI* roi = m_roiMap[1];

			if (roi != NULL) {
				MxMatrix mat;
				mat = roi->GetLocal2World();
				m_unk0x78 = new MxMatrix(mat);
			}
		}
	}

	if ((m_action->GetDuration() == -1 ||
		 ((MxDSMediaAction*) m_action)->GetSustainTime() == -1) &&
		m_compositePresenter) {
		m_compositePresenter->VTable0x60(this);
	} else {
		m_action->SetUnknown90(Timer()->GetTime());
	}

	ProgressTickleState(e_streaming);

	if (m_compositePresenter &&
		m_compositePresenter->IsA("LegoAnimMMPresenter")) {
		m_unk0x96 =
			((LegoAnimMMPresenter*) m_compositePresenter)->FUN_1004b8b0();
		m_compositePresenter->VTable0x60(this);
	}

	VTable0x8c();

done:
	if (m_unk0x70 != NULL) {
		delete m_unk0x70;
		m_unk0x70 = NULL;
	}
}

void LegoAnimPresenter::StreamingTickle() {
	if (m_subscriber->PeekData()) {
		MxStreamChunk* chunk = m_subscriber->PopData();
		m_subscriber->FreeDataChunk(chunk);
	}

	if (m_unk0x95) {
		ProgressTickleState(e_done);
		if (m_compositePresenter) {
			if (m_compositePresenter->IsA("LegoAnimMMPresenter")) {
				m_compositePresenter->VTable0x60(this);
			}
		}
	} else {
		if (m_action->GetElapsedTime() >
			m_anim->GetDuration() + m_action->GetStartTime()) {
			m_unk0x95 = TRUE;
		}
	}
}

void LegoAnimPresenter::DoneTickle() {
	MxVideoPresenter::DoneTickle();
}

MxResult LegoAnimPresenter::AddToManager() {
	return MxVideoPresenter::AddToManager();
}

void LegoAnimPresenter::Destroy() {
	Destroy(FALSE);
}

const char* LegoAnimPresenter::GetActionObjectName() {
	return m_action->GetObjectName();
}

void LegoAnimPresenter::FUN_1006b900(
	LegoAnim* p_anim,
	MxLong p_time,
	Matrix4* p_matrix
) {
	LegoTreeNode* root = p_anim->GetRoot();
	MxMatrix mat;
	LegoAnimNodeData* data = (LegoAnimNodeData*) root->GetData();

	if (p_matrix != NULL) {
		mat = *p_matrix;
	} else {
		LegoROI* roi = m_roiMap[data->GetUnknown0x20()];

		if (roi != NULL) {
			mat = roi->GetLocal2World();
		} else {
			mat.SetIdentity();
		}
	}

	LegoROI::FUN_100a8fd0(root, mat, p_time, m_roiMap);
}

void LegoAnimPresenter::FUN_1006b9a0(
	LegoAnim* p_anim,
	MxLong p_time,
	Matrix4* p_matrix
) {
	LegoTreeNode* root = p_anim->GetRoot();
	MxMatrix mat;
	LegoAnimNodeData* data = (LegoAnimNodeData*) root->GetData();

	if (p_matrix != NULL) {
		mat = *p_matrix;
	} else {
		LegoROI* roi = m_roiMap[data->GetUnknown0x20()];

		if (roi != NULL) {
			mat = roi->GetLocal2World();
		} else {
			mat.SetIdentity();
		}
	}

	if (p_anim->GetCamAnim() != NULL) {
		MxMatrix transform(mat);
		p_anim->GetCamAnim()->FUN_1009f490(p_time, transform);

		if (m_currentWorld != NULL &&
			m_currentWorld->GetCameraController() != NULL) {
			m_currentWorld->GetCameraController()->FUN_100123e0(transform, 0);
		}
	}

	LegoROI::FUN_100a8e80(root, mat, p_time, m_roiMap);
}

void LegoAnimPresenter::ParseExtra() {
	MxU16 extraLength;
	char* extraData;
	m_action->GetExtra(extraLength, extraData);

	if (extraLength) {
		char extraCopy[256];
		memcpy(extraCopy, extraData, extraLength);
		extraCopy[extraLength] = '\0';

		char output[256];
		if (KeyValueStringParse(NULL, g_strFROM_PARENT, extraCopy) &&
			m_compositePresenter != NULL) {
			m_compositePresenter->GetAction()->GetExtra(extraLength, extraData);

			if (extraLength) {
				memcpy(extraCopy, extraData, extraLength);
				extraCopy[extraLength] = '\0';
			}
		}

		if (KeyValueStringParse(output, g_strHIDE_ON_STOP, extraCopy)) {
			m_flags |= c_hideOnStop;
		}

		if (KeyValueStringParse(output, g_strMUST_SUCCEED, extraCopy)) {
			m_flags |= c_mustSucceed;
		}

		if (KeyValueStringParse(output, g_strSUBST, extraCopy)) {
			m_substMap = new LegoAnimSubstMap();

			char* substToken = output;
			char *key, *value;

			while ((key = strtok(substToken, g_parseExtraTokens))) {
				substToken = NULL;

				if ((value = strtok(NULL, g_parseExtraTokens))) {
					char* keyCopy = new char[strlen(key) + 1];
					strcpy(keyCopy, key);
					char* valueCopy = new char[strlen(value) + 1];
					strcpy(valueCopy, value);
					(*m_substMap)[keyCopy] = valueCopy;
				}
			}
		}

		if (KeyValueStringParse(output, g_strWORLD, extraCopy)) {
			char* token = strtok(output, g_parseExtraTokens);
			m_worldAtom = MxAtomId(token, e_lowerCase2);

			token = strtok(NULL, g_parseExtraTokens);
			m_worldId = atoi(token);
		}

		if (KeyValueStringParse(output, g_strPTATCAM, extraCopy)) {
			list<char*> tmp;

			if (m_unk0x90 != NULL) {
				for (MxS32 i = 0; i < m_unk0x94; i++) {
					if (m_unk0x90[i] != NULL) {
						// (modernization) critical bug: wrong free
						delete[] m_unk0x90;
					}
				}

				delete[] m_unk0x90;
				m_unk0x90 = NULL;
			}

			if (m_unk0x8c != NULL) {
				delete[] m_unk0x8c;
				m_unk0x8c = NULL;
			}

			char* token = strtok(output, g_parseExtraTokens);
			while (token != NULL) {
				char* valueCopy = new char[strlen(token) + 1];
				strcpy(valueCopy, token);
				tmp.push_back(valueCopy);
				token = strtok(NULL, g_parseExtraTokens);
			}

			m_unk0x94 = tmp.size();
			if (m_unk0x94 != 0) {
				m_unk0x8c = new LegoROI*[m_unk0x94];
				m_unk0x90 = new char*[m_unk0x94];
				memset(m_unk0x8c, 0, sizeof(*m_unk0x8c) * m_unk0x94);
				memset(m_unk0x90, 0, sizeof(*m_unk0x90) * m_unk0x94);

				MxS32 i = 0;
				for (list<char*>::iterator it = tmp.begin(); it != tmp.end();
					 it++, i++) {
					m_unk0x90[i] = *it;
				}
			}
		}
	}
}

void LegoAnimPresenter::VTable0xa0(Matrix4& p_matrix) {
	if (m_unk0x78 != NULL) {
		delete m_unk0x78;
	}

	m_unk0x78 = new MxMatrix(p_matrix);
}

MxResult LegoAnimPresenter::StartAction(
	MxStreamController* p_controller,
	MxDSAction* p_action
) {
	MxResult result = MxVideoPresenter::StartAction(p_controller, p_action);
	m_displayZ = 0;
	return result;
}

void LegoAnimPresenter::EndAction() {
	undefined4 unused; // required for match

	if (m_action == NULL) {
		return;
	}

	LegoWorld* world = CurrentWorld();

	if (world != NULL) {
		LegoEndAnimNotificationParam param(c_notificationEndAnim, NULL, 0);
		NotificationManager()->Send(world, param);
	}

	if (m_anim != NULL) {
		FUN_1006b9a0(m_anim, m_anim->GetDuration(), m_unk0x78);
	}

	if (m_roiMapSize != 0 && m_roiMap != NULL && m_roiMap[1] != NULL &&
		m_flags & c_hideOnStop) {
		for (MxS16 i = 1; i <= m_roiMapSize; i++) {
			if (m_roiMap[i] != NULL) {
				m_roiMap[i]->SetVisibility(FALSE);
			}
		}
	}

	FUN_1006c8a0(FALSE);
	FUN_1006ab70();
	VTable0x90();

	if (m_currentWorld != NULL) {
		m_currentWorld->Remove(this);
	}

	MxVideoPresenter::EndAction();
}

void LegoAnimPresenter::FUN_1006c7a0() {
	if (m_anim != NULL) {
		FUN_1006b9a0(m_anim, m_anim->GetDuration(), m_unk0x78);
	}

	m_unk0x95 = TRUE;
}

void LegoAnimPresenter::VTable0x8c() {
	if (m_unk0x78) {
		m_unk0xa8 += (*m_unk0x78)[3];
	} else {
		m_unk0xa8 += m_action->GetLocation();
	}

	if (m_currentWorld == NULL) {
		m_currentWorld = m_worldId != -1 ? FindWorld(m_worldAtom, m_worldId)
										 : CurrentWorld();
	}

	if (m_currentWorld) {
		m_currentWorld->FUN_1001fda0(this);
		if (!m_compositePresenter ||
			!m_compositePresenter->IsA("LegoAnimMMPresenter")) {
			m_currentWorld->Add(this);
		}
	}
}

void LegoAnimPresenter::VTable0x90() {
	if (m_currentWorld != NULL) {
		m_currentWorld->FUN_1001fe90(this);

		if (m_compositePresenter != NULL &&
			m_compositePresenter->IsA("LegoAnimMMPresenter")) {
			return;
		}

		m_currentWorld->Remove(this);
	}
}

void LegoAnimPresenter::FUN_1006c8a0(MxBool p_bool) {
	if (m_roiMapSize != 0 && m_roiMap != NULL) {
		for (MxU32 i = 1; i <= m_roiMapSize; i++) {
			LegoEntity* entity = m_roiMap[i]->GetEntity();

			if (entity != NULL) {
				if (p_bool) {
					entity->SetUnknown0x10Flag(LegoEntity::c_altBit1);
				} else {
					entity->ClearUnknown0x10Flag(LegoEntity::c_altBit1);
				}
			}
		}
	}
}

MxU32 LegoAnimPresenter::VTable0x94(
	Vector3& p_v1,
	Vector3& p_v2,
	float p_f1,
	float p_f2,
	Vector3& p_v3
) {
	Mx3DPointFloat a, b;

	b = p_v2;
	b *= p_f1;
	b += p_v1;

	a = b;
	a -= m_unk0xa8;

	float len = a.LenSquared();
	if (len <= 0.0f) {
		return TRUE;
	}

	len = sqrt(len);
	if (len <= m_unk0xa4 + p_f2 && m_roiMapSize != 0 && m_roiMap != NULL) {
		for (MxU32 i = 1; i <= m_roiMapSize; i++) {
			if (m_roiMap[i]->GetLODCount() != 0 &&
				m_roiMap[i]
					->FUN_100a9410(p_v1, p_v2, p_f1, p_f2, p_v3, FALSE)) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

MxResult LegoAnimPresenter::VTable0x98(LegoPathBoundary* p_boundary) {
	for (MxU32 i = 1; i <= m_roiMapSize; i++) {
		LegoEntity* entity = m_roiMap[i]->GetEntity();

		if (entity != NULL) {
			p_boundary->AddActor((LegoPathActor*) entity);
		}
	}

	return SUCCESS;
}
