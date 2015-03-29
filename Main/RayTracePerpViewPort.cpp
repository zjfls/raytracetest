#include "stdafx.h"
#include "RayTracePerpViewPort.h"
#include "RayTraceCamera.h"
#include "Transform.h"
#include "IWorldObj.h"

RayTracePerpViewPort::RayTracePerpViewPort()
{
}


RayTracePerpViewPort::~RayTracePerpViewPort()
{
}

void RayTracePerpViewPort::OnTransformChanged(const RayTraceCamera* pCamera)
{
	Transform* pTrans = pCamera->m_pOwnerObj->m_pTransform;
	Vector3 vecForward = pTrans->GetForward();
	vecForward.normalize();
	m_vecPlanePos = pTrans->GetWorldTranslate() + vecForward * m_fNear;
	m_vecPlaneNormal = -vecForward;



	Vector3 vecUp = pTrans->GetUp();
	Vector3 vecRight = pTrans->GetRight();
	vecUp.normalize();
	vecRight.normalize();


	float fHalfHeight = m_fNear * tan(m_fVertFov / 2.0f);
	float fHalfWidth = m_fNear * tan(m_fHorzFov / 2);


	m_vecPt[0] = pTrans->GetWorldTranslate() + vecForward * m_fNear + vecUp * fHalfHeight - vecRight * fHalfWidth;//tl
	m_vecPt[1] = pTrans->GetWorldTranslate() + vecForward * m_fNear + vecUp * fHalfHeight + vecRight * fHalfWidth;//tr
	m_vecPt[2] = pTrans->GetWorldTranslate() + vecForward * m_fNear - vecUp * fHalfHeight - vecRight * fHalfWidth;//bl
	m_vecPt[3] = pTrans->GetWorldTranslate() + vecForward * m_fNear - vecUp * fHalfHeight + vecRight * fHalfWidth;//br
}

