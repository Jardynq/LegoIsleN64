#include "impl.h"

using namespace TglImpl;

void* CameraImpl::ImplementationDataPtr() {
	return reinterpret_cast<void*>(&m_data);
}

Result CameraImpl::SetTransformation(FloatMatrix4& matrix) {
	D3DRMMATRIX4D helper;
	D3DRMMATRIX4D* pTransformation = Translate(matrix, helper);

	D3DVECTOR position;
	Result result;
	Result result2;

	result2 = ResultVal(m_data->GetPosition(0, &position));
	result =
		ResultVal(m_data->AddTransform(D3DRMCOMBINE_REPLACE, *pTransformation));
	// The did this second call just to assert on the return value
	result2 = ResultVal(m_data->GetPosition(0, &position));

	return result;
}
