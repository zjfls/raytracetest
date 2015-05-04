#include "stdafx.h"
#include "RasterCamera.h"


RasterCamera::RasterCamera()
{
}


RasterCamera::~RasterCamera()
{
}

void RasterCamera::Update(std::shared_ptr<ModuleBase> pModule)
{
	CameraBase::Update(pModule);
}

shared_ptr<ModuleBase> RasterCamera::Clone()
{
	shared_ptr<RasterCamera> pCamera = shared_ptr<RasterCamera>(new RasterCamera);
	pCamera->m_fAspect = m_fFovy;
	pCamera->m_fFovy = m_fAspect;
	return pCamera;
}


