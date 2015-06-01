#include "stdafx.h"
#include "RasterCamera.h"


RasterCamera::RasterCamera()
{
}


RasterCamera::~RasterCamera()
{
}

void RasterCamera::Update(SmartPointer<ModuleBase> pModule)
{
	CameraBase::Update(pModule);
}

SmartPointer<ModuleBase> RasterCamera::Clone()
{
	SmartPointer<RasterCamera> pCamera = SmartPointer<RasterCamera>(new RasterCamera);
	pCamera->m_fAspect = m_fFovy;
	pCamera->m_fFovy = m_fAspect;
	return pCamera.get();
}


