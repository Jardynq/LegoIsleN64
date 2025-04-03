#ifndef __LEGOMESH_H
#define __LEGOMESH_H

#include "color.h"

class LegoStorage;

struct LegoMeshUnkComponent {
	~LegoMeshUnkComponent() {
		if (m_unk0x08) {
			delete m_unk0x08;
		}
		if (m_unk0x0c) {
			delete m_unk0x0c;
		}
		if (m_unk0x10) {
			delete m_unk0x10;
		}
		if (m_unk0x14) {
			delete m_unk0x14;
		}
		if (m_unk0x18) {
			delete m_unk0x18;
		}
	}

	undefined m_unk0x00[8];
	undefined* m_unk0x08;
	undefined* m_unk0x0c;
	undefined* m_unk0x10;
	undefined* m_unk0x14;
	undefined* m_unk0x18;
};

class LegoMesh {
public:
	enum { e_flat, e_gouraud, e_wireframe };

	LegoMesh();
	virtual ~LegoMesh();
	LegoColor GetColor() { return m_color; }
	void SetColor(LegoColor p_color) { m_color = p_color; }
	LegoFloat GetAlpha() { return m_alpha; }
	LegoU8 GetShading() { return m_shading; }
	void SetShading(LegoU8 p_shading) { m_shading = p_shading; }
	LegoU8 GetUnknown0x0d() { return m_unk0x0d; }
	const LegoChar* GetTextureName() { return m_textureName; }
	const LegoChar* GetMaterialName() { return m_materialName; }
	LegoBool GetUnknown0x21() { return m_unk0x21; }
	LegoResult Read(LegoStorage* p_storage);

	// LegoMesh::`scalar deleting destructor'

protected:
	LegoColor m_color;
	LegoFloat m_alpha;
	LegoU8 m_shading;
	LegoU8 m_unk0x0d;
	LegoMeshUnkComponent* m_unk0x10;
	undefined4 m_unk0x14;
	LegoChar* m_textureName;
	LegoChar* m_materialName;
	undefined m_unk0x20;
	LegoBool m_unk0x21;
};

#endif // __LEGOMESH_H
