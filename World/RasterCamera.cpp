#include "stdafx.h"
#include "RasterCamera.h"


RasterCamera::RasterCamera()
{
}


RasterCamera::~RasterCamera()
{
}

void RasterCamera::Update()
{
	CameraBase::Update();
}

ModuleBase* RasterCamera::Clone()
{
	RasterCamera* pCamera = new RasterCamera;
	pCamera->m_fAspect = m_fFovy;
	pCamera->m_fFovy = m_fAspect;
	return pCamera;
}


