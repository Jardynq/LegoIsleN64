#include "viewroi.h"

#include <vec.h>

undefined g_unk101013d8 = 0;

float ViewROI::IntrinsicImportance() const {
	return .5;
} // for now

Tgl::Group* ViewROI::GetGeometry() {
	return geometry;
}

const Tgl::Group* ViewROI::GetGeometry() const {
	return geometry;
}

void ViewROI::UpdateWorldData(const Matrix4& parent2world) {
	OrientableROI::UpdateWorldData(parent2world);

	if (geometry) {
		Matrix4 in {0};
		SETMAT4(in, m_local2world);
		Tgl::Result result = geometry->SetTransformation(in);
		(void)result;
		// assert(Tgl::Succeeded(result));
	}
}

void ViewROI::VTable0x24(const Matrix4& p_transform) {
	OrientableROI::VTable0x24(p_transform);
	if (geometry) {
		Matrix4 in {0};
		SETMAT4(in, m_local2world);
		geometry->SetTransformation(in);
	}
}

void ViewROI::SetLocalTransform(const Matrix4& p_transform) {
	OrientableROI::SetLocalTransform(p_transform);
	if (geometry) {
		Matrix4 in {0};
		SETMAT4(in, m_local2world);
		geometry->SetTransformation(in);
	}
}

void ViewROI::VTable0x1c() {
	OrientableROI::VTable0x1c();
	if (geometry) {
		Matrix4 in {0};
		SETMAT4(in, m_local2world);
		geometry->SetTransformation(in);
	}
}

undefined ViewROI::SetUnk101013d8(undefined p_flag) {
	undefined oldFlag = g_unk101013d8;
	g_unk101013d8 = p_flag;
	return oldFlag;
}
