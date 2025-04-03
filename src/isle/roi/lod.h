#pragma once

#include "view_lod.h"

class LegoTextureContainer;
class LegoTextureInfo;
class LegoStorage;

class LegoLOD : public ViewLOD {
public:
	struct Mesh {
		Tgl::Mesh* m_tglMesh;
		BOOL m_unk0x04;
	};

	LegoLOD(Tgl::Renderer*);
	~LegoLOD() override;

	int NumPolys() const override { return m_numPolys; }

	float VTable0x10() override { return 0.0; }

	LegoResult Read(
		Tgl::Renderer* p_renderer,
		LegoTextureContainer* p_textureContainer,
		LegoStorage* p_storage
	);
	LegoLOD* Clone(Tgl::Renderer* p_renderer);
	LegoResult FUN_100aacb0(
		LegoFloat p_red,
		LegoFloat p_green,
		LegoFloat p_blue,
		LegoFloat p_alpha
	);
	LegoResult FUN_100aad00(LegoTextureInfo* p_textureInfo);
	LegoResult FUN_100aad70(LegoTextureInfo* p_textureInfo);
	void FUN_100aae60();
	LegoResult GetTexture(LegoTextureInfo*& p_textureInfo);

	static LegoBool FUN_100aae20(const LegoChar* p_name);

	// LegoLOD::`scalar deleting destructor'

protected:
	Mesh* m_melems;
	LegoU32 m_numMeshes;
	LegoU32 m_numVertices;
	LegoU32 m_numPolys;
	undefined4 m_unk0x1c;
};

