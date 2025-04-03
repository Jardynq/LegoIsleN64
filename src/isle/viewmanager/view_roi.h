#pragma once

#include "lod_list.h"
#include "orientable_roi.h"
#include "tgl.h"
#include "view_lod_list.h"

/*
	ViewROI objects represent view objects, collections of view objects,
	etc. Basically, anything which can be placed in a scene and manipilated
	by the view manager is a ViewROI.
*/

class ViewROI : public OrientableROI {
public:
	ViewROI(Tgl::Renderer* pRenderer, ViewLODList* lodList)
		: geometry(pRenderer->CreateGroup()), m_unk0xe0(-1) {
		SetLODList(lodList);
	}

	~ViewROI() override {
		// SetLODList() will decrease refCount of LODList
		SetLODList(0);
		delete geometry;
	}

	void SetLODList(ViewLODList* lodList) {
		// ??? inherently type unsafe - kind of... because, now, ROI
		//     does not expose SetLODs() ...
		// solution: create pure virtual LODListBase* ROI::GetLODList()
		// and let derived ROI classes hold the LODList

		if (lods) {
			reinterpret_cast<ViewLODList*>(lods)->Release();
		}

		lods = (LODListBase*) lodList;

		if (lods) {
			reinterpret_cast<ViewLODList*>(lods)->AddRef();
		}
	}

	float IntrinsicImportance() const override;
	void VTable0x1c() override;
	void SetLocalTransform(const Matrix4& p_transform) override;
	void VTable0x24(const Matrix4& p_transform) override;
	virtual Tgl::Group* GetGeometry();
	virtual const Tgl::Group* GetGeometry() const;

	int GetUnknown0xe0() { return m_unk0xe0; }
	void SetUnknown0xe0(int p_unk0xe0) { m_unk0xe0 = p_unk0xe0; }

	static undefined SetUnk101013d8(undefined p_flag);

protected:
	void UpdateWorldData(const Matrix4& parent2world) override;

	Tgl::Group* geometry;
	int m_unk0xe0;
};

// ViewROI::`scalar deleting destructor'

