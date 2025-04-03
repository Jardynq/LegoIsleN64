#pragma once

#include "mx_matrix.h"
#include "roi.h"

class OrientableROI : public ROI {
public:
	enum { c_bit1 = 0x01, c_bit2 = 0x02 };

	OrientableROI();

	const float* GetWorldVelocity() const override;
	const BoundingBox& GetWorldBoundingBox() const override;
	const BoundingSphere& GetWorldBoundingSphere() const override;

	virtual void VTable0x14() { VTable0x1c(); }

	virtual void UpdateWorldBoundingVolumes() = 0;
	virtual void VTable0x1c();
	virtual void SetLocalTransform(const Matrix4& p_transform);
	virtual void VTable0x24(const Matrix4& p_transform);
	virtual void UpdateWorldData(const Matrix4& p_transform);
	virtual void UpdateWorldVelocity();

	void WrappedSetLocalTransform(const Matrix4& p_transform);
	void UpdateTransformationRelativeToParent(const Matrix4& p_transform);
	void WrappedVTable0x24(const Matrix4& p_transform);
	void GetLocalTransform(Matrix4& p_transform);
	void FUN_100a58f0(const Matrix4& p_transform);
	void FUN_100a5a30(const Vector3& p_world_velocity);

	const Matrix4& GetLocal2World() const { return m_local2world; }

	const float* GetWorldPosition() const { return m_local2world[3]; }

	const float* GetWorldDirection() const { return m_local2world[2]; }

	const float* GetWorldUp() const { return m_local2world[1]; }

	OrientableROI* GetParentROI() const { return m_parentROI; }

	void SetParentROI(OrientableROI* p_parentROI) { m_parentROI = p_parentROI; }

	void ToggleUnknown0xd8(BOOL p_enable) {
		if (p_enable) {
			m_unk0xd8 |= c_bit1 | c_bit2;
		} else {
			m_unk0xd8 &= ~c_bit1;
		}
	}

protected:
	MxMatrix m_local2world;
	BoundingBox m_world_bounding_box;
	BoundingBox m_unk0x80;
	BoundingSphere m_world_bounding_sphere;
	Mx3DPointFloat m_world_velocity;
	OrientableROI* m_parentROI;
	undefined4 m_unk0xd8;
};

// OrientableROI::`scalar deleting destructor'

// OrientableROI::~OrientableROI

