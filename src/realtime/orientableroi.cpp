#include "orientableroi.h"

#include <vec.h>

OrientableROI::OrientableROI() {
	FILLVEC3(m_world_bounding_box.Min(), 888888.8);
	FILLVEC3(m_world_bounding_box.Max(), -888888.8);
	ZEROVEC3(m_world_bounding_sphere.Center());
	m_world_bounding_sphere.Radius() = 0.0;
	ZEROVEC3(m_world_velocity);
	IDENTMAT4(m_local2world);

	m_parentROI = NULL;
	ToggleUnknown0xd8(TRUE);
}

// Maybe an overload based on MxMatrix type

void OrientableROI::WrappedSetLocalTransform(const Matrix4& p_transform) {
	SetLocalTransform(p_transform);
}

void OrientableROI::UpdateTransformationRelativeToParent(
	const Matrix4& p_transform
) {
	MxMatrix mat;

	double local2world[4][4];
	double local2parent[4][4];
	int i = 0, j = 0;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			local2world[i][j] = p_transform[i][j];
			local2parent[i][j] = m_local2world[i][j];
		}
	}

	double local_inverse[4][4];
	INVERTMAT4d(local_inverse, local2parent);

	double parent2world[4][4];
	MXM4(parent2world, local_inverse, local2world);

	unsigned int k = 0, l = 0;
	for (k = 0; k < 4; k++) {
		for (l = 0; l < 4; l++) {
			mat[k][l] = parent2world[k][l];
		}
	}

	UpdateWorldData(mat);
}

// Maybe an overload based on MxMatrix type

void OrientableROI::WrappedVTable0x24(const Matrix4& p_transform) {
	VTable0x24(p_transform);
}

void OrientableROI::GetLocalTransform(Matrix4& p_transform) {
	MxMatrix mat;

	if (m_parentROI != NULL) {
		double local2parent[4][4];
		unsigned int i = 0, j = 0;

		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				local2parent[i][j] = m_parentROI->GetLocal2World()[i][j];
			}
		}

		double local_inverse[4][4];
		INVERTMAT4d(local_inverse, local2parent);

		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				mat[i][j] = local_inverse[i][j];
			}
		}

		MXM4(p_transform, m_local2world, mat);
	} else {
		p_transform = m_local2world;
	}
}

void OrientableROI::FUN_100a58f0(const Matrix4& p_transform) {
	m_local2world = p_transform;
	ToggleUnknown0xd8(TRUE);
}

void OrientableROI::VTable0x1c() {
	UpdateWorldBoundingVolumes();
	UpdateWorldVelocity();
}

void OrientableROI::SetLocalTransform(const Matrix4& p_transform) {
	m_local2world = p_transform;
	UpdateWorldBoundingVolumes();
	UpdateWorldVelocity();
}

void OrientableROI::VTable0x24(const Matrix4& p_transform) {
	MxMatrix l_matrix(m_local2world);
	m_local2world.Product(p_transform, l_matrix);
	UpdateWorldBoundingVolumes();
	UpdateWorldVelocity();
}

void OrientableROI::UpdateWorldData(const Matrix4& p_transform) {
	MxMatrix l_matrix(m_local2world);
	m_local2world.Product(l_matrix, p_transform);
	UpdateWorldBoundingVolumes();
	UpdateWorldVelocity();

	// iterate over comps
	if (comp) {
		for (CompoundObject::iterator iter = comp->begin();
			 !(iter == comp->end());
			 iter++) {
			ROI* child = *iter;
			static_cast<OrientableROI*>(child)->UpdateWorldData(p_transform);
		}
	}
}

void OrientableROI::FUN_100a5a30(const Vector3& p_world_velocity) {
	m_world_velocity = p_world_velocity;
}

void OrientableROI::UpdateWorldVelocity() {
}

void CalcWorldBoundingVolumes(
	const BoundingSphere& modelling_sphere,
	const Matrix4& local2world,
	BoundingBox& world_bounding_box,
	BoundingSphere& world_bounding_sphere
) {
	// calculate world bounding volumes given a bounding sphere in modelling
	// space and local2world transform

	// ??? we need to transform the radius too... if scaling...

	V3XM4(
		world_bounding_sphere.Center(),
		modelling_sphere.Center(),
		local2world
	);

	world_bounding_sphere.Radius() = modelling_sphere.Radius();

	// update world_bounding_box
	world_bounding_box.Min()[0] =
		world_bounding_sphere.Center()[0] - world_bounding_sphere.Radius();
	world_bounding_box.Min()[1] =
		world_bounding_sphere.Center()[1] - world_bounding_sphere.Radius();
	world_bounding_box.Min()[2] =
		world_bounding_sphere.Center()[2] - world_bounding_sphere.Radius();
	world_bounding_box.Max()[0] =
		world_bounding_sphere.Center()[0] + world_bounding_sphere.Radius();
	world_bounding_box.Max()[1] =
		world_bounding_sphere.Center()[1] + world_bounding_sphere.Radius();
	world_bounding_box.Max()[2] =
		world_bounding_sphere.Center()[2] + world_bounding_sphere.Radius();
}

const float* OrientableROI::GetWorldVelocity() const {
	return m_world_velocity.GetData();
}

const BoundingBox& OrientableROI::GetWorldBoundingBox() const {
	return m_world_bounding_box;
}

const BoundingSphere& OrientableROI::GetWorldBoundingSphere() const {
	return m_world_bounding_sphere;
}
