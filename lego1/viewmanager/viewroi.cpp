#include "viewroi.h"

#include "utils.h"

#include <vec.h>


// GLOBAL: LEGO1 0x101013d8
undefined g_unk101013d8 = 0;

// FUNCTION: LEGO1 0x100a9eb0
float ViewROI::IntrinsicImportance() const {
	return .5;
} // for now

// FUNCTION: LEGO1 0x100a9ec0
Tgl::Group* ViewROI::GetGeometry() {
	return geometry;
}

// FUNCTION: LEGO1 0x100a9ed0
const Tgl::Group* ViewROI::GetGeometry() const {
	return geometry;
}

// FUNCTION: LEGO1 0x100a9ee0
void ViewROI::UpdateWorldData(const Matrix4& parent2world) {
	OrientableROI::UpdateWorldData(parent2world);

	if (geometry) {
		Tgl::FloatMatrix4 matrix;
		Matrix4 in(matrix);
		SETMAT4(in, m_local2world);
		Tgl::Result result = geometry->SetTransformation(matrix);
		// assert(Tgl::Succeeded(result));
	}
}

// FUNCTION: LEGO1 0x100a9fc0
void ViewROI::VTable0x24(const Matrix4& p_transform) {
	OrientableROI::VTable0x24(p_transform);
	if (geometry) {
		Tgl::FloatMatrix4 matrix;
		Matrix4 in(matrix);
		SETMAT4(in, m_local2world);
		geometry->SetTransformation(matrix);
	}
}

// FUNCTION: LEGO1 0x100aa0a0
void ViewROI::SetLocalTransform(const Matrix4& p_transform) {
	OrientableROI::SetLocalTransform(p_transform);
	if (geometry) {
		Tgl::FloatMatrix4 matrix;
		Matrix4 in(matrix);
		SETMAT4(in, m_local2world);
		geometry->SetTransformation(matrix);
	}
}

// FUNCTION: LEGO1 0x100aa180
void ViewROI::VTable0x1c() {
	OrientableROI::VTable0x1c();
	if (geometry) {
		Tgl::FloatMatrix4 matrix;
		Matrix4 in(matrix);
		SETMAT4(in, m_local2world);
		geometry->SetTransformation(matrix);
	}
}

// FUNCTION: LEGO1 0x100aa500
undefined ViewROI::SetUnk101013d8(undefined p_flag) {
	undefined oldFlag = g_unk101013d8;
	g_unk101013d8 = p_flag;
	return oldFlag;
}
