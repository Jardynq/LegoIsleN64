#ifndef MODELDB_H
#define MODELDB_H

#include "mxlist.h"
#include "mxstring.h"

#include <stdio.h>

struct ModelDbPart {
	MxResult Read(FILE* p_file);

	MxString m_roiName;
	undefined4 m_partDataLength;
	undefined4 m_partDataOffset;
};

class ModelDbPartList : public MxList<ModelDbPart*> {
public:
	ModelDbPartList() { m_unk0x18 = 1; }

	MxS8 Compare(ModelDbPart* p_a, ModelDbPart* p_b) override {
		MxS32 compare =
			strcmpi(p_a->m_roiName.GetData(), p_b->m_roiName.GetData());

		if (compare == 0) {
			p_b->m_partDataLength = p_a->m_partDataLength;
			p_b->m_partDataOffset = p_a->m_partDataOffset;
		}

		return compare;
	}

private:
	undefined m_unk0x18;
};

class ModelDbPartListCursor : public MxListCursor<ModelDbPart*> {
public:
	ModelDbPartListCursor(ModelDbPartList* p_list)
		: MxListCursor<ModelDbPart*>(p_list) {}
};

struct ModelDbModel {
	void Free();
	MxResult Read(FILE* p_file);

	char* m_modelName;
	undefined4 m_unk0x04;
	undefined4 m_unk0x08;
	char* m_presenterName;
	float m_location[3];
	float m_direction[3];
	float m_up[3];
	undefined m_unk0x34;
};

struct ModelDbWorld {
	char* m_worldName;
	ModelDbPartList* m_partList;
	ModelDbModel* m_models;
	MxS32 m_numModels;
	undefined m_unk0x10[0x08];
};

MxResult
ReadModelDbWorlds(FILE* p_file, ModelDbWorld*& p_worlds, MxS32& p_numWorlds);
void FreeModelDbWorlds(ModelDbWorld*& p_worlds, MxS32 p_numWorlds);

#endif // MODELDB_H
