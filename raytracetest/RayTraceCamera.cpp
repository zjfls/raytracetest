#include "stdafx.h"
#include "RayTraceCamera.h"
#include "RayTraceRender.h"
#include "IWorld.h"

RayTraceCamera::RayTraceCamera()
{
	m_pRender = new RayTraceRender;
}


RayTraceCamera::~RayTraceCamera()
{
}

void RayTraceCamera::Update()
{

}

void RayTraceCamera::OnLateUpdate()
{

}

void RayTraceCamera::Render()
{
	RayTraceRender* pRender = dynamic_cast<RayTraceRender*>(m_pRender);
	if (nullptr == pRender)
	{
		return;
	}
	pRender->Render(this, IWorld::pSingleWorld);

}
