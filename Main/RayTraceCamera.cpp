#include "stdafx.h"
#include "RayTraceCamera.h"
#include "RayTraceRender.h"
#include "RayTracePerpViewPort.h"
#include "IWorld.h"
#include "IRender.h"

RayTraceCamera::RayTraceCamera()
{
	//m_pRender = new RayTraceRender;
	m_pViewPort = nullptr;
}


RayTraceCamera::~RayTraceCamera()
{
	//if (m_pRender != nullptr)
	//{
	//	delete m_pRender;
	//	m_pRender = nullptr;
	//}
	if (m_pViewPort != nullptr)
	{
		delete m_pViewPort;
		m_pViewPort = nullptr;
	}

	
}

void RayTraceCamera::Update()
{
	//if (m_pOwnerObj->m_pTransform->m_bThisFrameUpdated)
	//{
	//	m_pViewPort->OnTransformChanged(this);
	//}
}

void RayTraceCamera::OnLateUpdate()
{

}

void RayTraceCamera::Render()
{
	//RayTraceRender* pRender = dynamic_cast<RayTraceRender*>(m_pRender);
	//if (nullptr == pRender)
	//{
	//	return;
	//}
	//pRender->Render(this, IWorld::pSingleWorld);

}

//
void RayTraceCamera::SetPerpViewPort(float fNear, float fFar, float fVertFov, float fHorzFov, int pixWidth, int pixHeight)
{
	//if (m_pOwnerObj == nullptr)
	//{
	//	return;
	//}
	//RayTracePerpViewPort* pPerpVp = new RayTracePerpViewPort;
	//m_pViewPort = pPerpVp;
	//pPerpVp->m_fHorzFov = fHorzFov;
	//pPerpVp->m_fVertFov = fVertFov;
	//pPerpVp->m_fNear = fNear;
	//pPerpVp->m_pixHeight = pixHeight;
	//pPerpVp->m_pixWidth = pixWidth;



	




}

//RayTraceCameraCreator::RayTraceCameraCreator()
//{
//
//}
//
//RayTraceCameraCreator::~RayTraceCameraCreator()
//{
//
//}
//
//ModuleBase* RayTraceCameraCreator::CreateModule()
//{
//	return new RayTraceCamera();
//}
