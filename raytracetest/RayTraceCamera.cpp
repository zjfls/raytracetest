#include "stdafx.h"
#include "RayTraceCamera.h"
#include "RayTraceRender.h"
#include "RayTracePerpViewPort.h"
#include "IWorld.h"

RayTraceCamera::RayTraceCamera()
{
	m_pRender = new RayTraceRender;
	m_pViewPort = nullptr;
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

void RayTraceCamera::SetPerpViewPort(float fNear, float fFar, float fVertFov, float fHorzFov)
{
	if (m_pOwnerObj == nullptr)
	{
		return;
	}
	RayTracePerpViewPort* pPerpVp = new RayTracePerpViewPort;
	Transform* pTrans = m_pOwnerObj->m_pTransform;



}
