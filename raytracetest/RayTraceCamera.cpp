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

//
void RayTraceCamera::SetPerpViewPort(float fNear, float fFar, float fVertFov, float fHorzFov, int pixWidth, int pixHeight)
{
	if (m_pOwnerObj == nullptr)
	{
		return;
	}
	RayTracePerpViewPort* pPerpVp = new RayTracePerpViewPort;
	m_pViewPort = pPerpVp;
	Transform* pTrans = m_pOwnerObj->m_pTransform;


	Vector3 vecForward = pTrans->GetForward();
	vecForward.normalize();
	pPerpVp->m_vecPlanePos = pTrans->m_vecTranslate + vecForward * fNear;
	pPerpVp->m_vecPlaneNormal = -vecForward;
	pPerpVp->m_pixHeight = pixHeight;
	pPerpVp->m_pixWidth = pixWidth;


	Vector3 vecUp = pTrans->GetUp();
	Vector3 vecRight = pTrans->GetRight();
	vecUp.normalize();
	vecRight.normalize();


	float fHalfHeight = fNear * tan(fVertFov / 2.0f);
	float fHalfWidth = fNear * tan(fHorzFov / 2);


	pPerpVp->m_vecPt[0] = vecForward * fNear + vecUp * fHalfHeight - vecRight * fHalfWidth;//tl
	pPerpVp->m_vecPt[1] = vecForward * fNear + vecUp * fHalfHeight + vecRight * fHalfWidth;//tr
	pPerpVp->m_vecPt[2] = vecForward * fNear - vecUp * fHalfHeight - vecRight * fHalfWidth;//bl
	pPerpVp->m_vecPt[3] = vecForward * fNear - vecUp * fHalfHeight + vecRight * fHalfWidth;//br
	




}
