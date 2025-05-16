#include "mx_ds_object.h"

#include "mx_ds_action.h"
#include "mx_ds_anim.h"
#include "mx_ds_event.h"
#include "mx_ds_file.h"
#include "mx_ds_media_action.h"
#include "mx_ds_multi_action.h"
#include "mx_ds_object_action.h"
#include "mx_ds_parallel_action.h"
#include "mx_ds_select_action.h"
#include "mx_ds_serial_action.h"
#include "mx_ds_sound.h"
#include "mx_ds_still.h"
#include "mx_utilities.h"

#include <stdlib.h>
#include <string.h>

MxDSObject::MxDSObject() {
	m_type = e_object;
	m_sourceName = NULL;
	m_unk0x14 = 0;
	m_objectName = NULL;
	m_objectId = -1;
	m_unk0x24 = -1;
	m_unk0x28 = NULL;
}

MxDSObject::~MxDSObject() {
	delete[] m_objectName;
	delete[] m_sourceName;
}

void MxDSObject::CopyFrom(MxDSObject& p_dsObject) {
	SetSourceName(p_dsObject.m_sourceName);
	m_unk0x14 = p_dsObject.m_unk0x14;
	SetObjectName(p_dsObject.m_objectName);
	m_objectId = p_dsObject.m_objectId;
	m_unk0x24 = p_dsObject.m_unk0x24;
	m_atomId = p_dsObject.m_atomId;
	m_unk0x28 = p_dsObject.m_unk0x28;
}

MxDSObject::MxDSObject(MxDSObject& p_dsObject) {
	CopyFrom(p_dsObject);
}

MxDSObject& MxDSObject::operator=(MxDSObject& p_dsObject) {
	if (this == &p_dsObject) {
		return *this;
	}

	CopyFrom(p_dsObject);
	return *this;
}

void MxDSObject::SetObjectName(const char* p_objectName) {
	if (p_objectName == m_objectName) {
		return;
	}

	delete[] m_objectName;

	if (p_objectName) {
		m_objectName = new char[strlen(p_objectName) + 1];

		if (m_objectName) {
			strcpy(m_objectName, p_objectName);
		}
	} else {
		m_objectName = NULL;
	}
}

void MxDSObject::SetSourceName(const char* p_sourceName) {
	if (p_sourceName == m_sourceName) {
		return;
	}

	delete[] m_sourceName;

	if (p_sourceName) {
		m_sourceName = new char[strlen(p_sourceName) + 1];

		if (m_sourceName) {
			strcpy(m_sourceName, p_sourceName);
		}
	} else {
		m_sourceName = NULL;
	}
}

undefined4 MxDSObject::VTable0x14() {
	// DECOMP: Rendered as 8 + 2 in beta. Maybe a sizeof() call?
	return 10;
}

MxU32 MxDSObject::GetSizeOnDisk() {
	MxU32 sizeOnDisk = 0;

	sizeOnDisk += 2;

	if (m_sourceName) {
		sizeOnDisk += strlen(m_sourceName) + 1;
	} else {
		sizeOnDisk++;
	}

	sizeOnDisk += sizeof(m_unk0x14);

	if (m_objectName) {
		sizeOnDisk += strlen(m_objectName) + 1;
	} else {
		sizeOnDisk++;
	}

	sizeOnDisk += sizeof(m_objectId);

	m_sizeOnDisk = sizeOnDisk;
	return sizeOnDisk;
}

void MxDSObject::Deserialize(MxU8*& p_source, MxS16 p_unk0x24) {
	SetSourceName((char*) p_source);
	p_source += strlen(m_sourceName) + 1;

	m_unk0x14 = *(undefined4*) p_source;
	p_source += sizeof(m_unk0x14);

	SetObjectName((char*) p_source);
	p_source += strlen(m_objectName) + 1;

	m_objectId = *(MxU32*) p_source;
	p_source += sizeof(m_objectId);

	m_unk0x24 = p_unk0x24;
}

MxDSObject*
MxDSObjectList::FindInternal(MxDSObject* p_action, MxBool p_delete) {
	// DECOMP ALPHA 0x1008b99d ?

	MxDSObject* found = NULL;

	iterator it;
	for (it = begin(); it != end(); it++) {
		if (p_action->GetObjectId() == -1 ||
			p_action->GetObjectId() == (*it)->GetObjectId()) {
			if (p_action->GetUnknown24() == -2 ||
				p_action->GetUnknown24() == -3 ||
				p_action->GetUnknown24() == (*it)->GetUnknown24()) {
				found = *it;
				if (p_action->GetUnknown24() != -3) {
					break;
				}
			}
		}
	}

	if (p_delete && found != NULL) {
		erase(it);
	}

	return found;
}

MxDSObject* DeserializeDSObjectDispatch(MxU8*& p_source, MxS16 p_flags) {
	MxDSObject* obj = NULL;

	MxU16 type = *(MxU16*) p_source;
	p_source += 2;

	switch (type) {
	case MxDSObject::e_object:
		obj = new MxDSObject();
		break;
	case MxDSObject::e_action:
		obj = new MxDSAction();
		break;
	case MxDSObject::e_mediaAction:
		obj = new MxDSMediaAction();
		break;
	case MxDSObject::e_anim:
		obj = new MxDSAnim();
		break;
	case MxDSObject::e_sound:
		obj = new MxDSSound();
		break;
	case MxDSObject::e_event:
		obj = new MxDSEvent();
		break;
	case MxDSObject::e_still:
		obj = new MxDSStill();
		break;
	case MxDSObject::e_objectAction:
		obj = new MxDSObjectAction();
		break;
	case MxDSObject::e_multiAction:
		obj = new MxDSMultiAction();
		break;
	case MxDSObject::e_serialAction:
		obj = new MxDSSerialAction();
		break;
	case MxDSObject::e_parallelAction:
		obj = new MxDSParallelAction();
		break;
	case MxDSObject::e_selectAction:
		obj = new MxDSSelectAction();
		break;
	default:
		return NULL;
	}

	if (obj) {
		obj->Deserialize(p_source, p_flags);
	}

	return obj;
}
