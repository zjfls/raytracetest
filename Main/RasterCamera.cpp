#include "stdafx.h"
#include "RasterCamera.h"


RasterCamera::RasterCamera()
{
}


RasterCamera::~RasterCamera()
{
}

void RasterCamera::OnUpdate()
{
	CameraBase::OnUpdate();
}

SmartPointer<ModuleBase> RasterCamera::Clone()
{
	SmartPointer<RasterCamera> pCamera = SmartPointer<RasterCamera>(new RasterCamera);
	pCamera->m_fAspect = m_fFovy;
	pCamera->m_fFovy = m_fAspect;
	pCamera->m_bActive = m_bActive;
	return pCamera.get();
}


