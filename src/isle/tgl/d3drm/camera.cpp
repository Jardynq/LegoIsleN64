#include "impl.h"

using namespace TglImpl;

void* CameraImpl::ImplementationDataPtr() {
	return reinterpret_cast<void*>(&m_data);
}

Result CameraImpl::SetTransformation(Matrix4& matrix) {
	m_data->SetTransform(matrix);
	return Tgl::Success;
}
