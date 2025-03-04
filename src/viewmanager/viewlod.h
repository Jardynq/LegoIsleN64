#ifndef VIEWLOD_H
#define VIEWLOD_H

#include "realtime/roi.h"
#include "tgl/tgl.h"

//////////////////////////////////////////////////////////////////////////////
// ViewLOD
//

class ViewLOD : public LODObject {
public:
	enum { c_bit4 = 0x10 };

	ViewLOD(Tgl::Renderer* /*pRenderer*/) : m_meshBuilder(NULL), m_unk0x08(3) {}
	~ViewLOD() override;

	double AveragePolyArea() const override {
		return 2 * 3.14159 * 10.0 / NumPolys();
	}

	int NVerts() const override { return NumPolys() * 2; }

	Tgl::MeshBuilder* GetMeshBuilder() { return m_meshBuilder; }
	const Tgl::MeshBuilder* GetMeshBuilder() const { return m_meshBuilder; }
	undefined4 GetUnknown0x08() { return m_unk0x08; }
	unsigned char GetUnknown0x08Test4() { return m_unk0x08 & 0xffffff04; }
	unsigned char GetUnknown0x08Test8() { return m_unk0x08 & 0xffffff08; }

	void SetFlag(unsigned char p_flag) { m_unk0x08 |= p_flag; }
	void ClearFlag(unsigned char p_flag) { m_unk0x08 &= ~p_flag; }

	// ViewLOD::`scalar deleting destructor'

protected:
	Tgl::MeshBuilder* m_meshBuilder;
	undefined4 m_unk0x08;
};

#endif // VIEWLOD_H
