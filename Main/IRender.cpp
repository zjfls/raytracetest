#include "stdafx.h"
#include "IRender.h"
#include "CameraBase.h"
#include "Event.h"

IRender::IRender()
	:m_pCurrentRenderCamera(nullptr)
	//, m_pTarget(nullptr)
{
}


IRender::~IRender()
{
}

void IRender::SetRenderTarget(int nIndex, IRenderTarget* pTarget)
{
	//m_TargetGroup.m_Map[nIndex] = pTarget;
}



void IRender::SetCurrentRenderCamera(SmartPointer<CameraBase> pCamera)
{
	m_pCurrentRenderCamera = pCamera;
}

void IRender::OnCameraRender(CameraRenderEvent& rEvent)
{
	RenderCamera(rEvent);
}

void IRender::RegistCamera(SmartPointer<CameraBase> pCamera)
{
	pCamera->getEvent<CameraRenderEvent>("CAMERARENDER")->addEventHandler(this, std::bind(&IRender::OnCameraRender, this, std::placeholders::_1));
	pCamera->getEvent<CameraRenderEvent>("CAMERAUPDATE")->addEventHandler(this, std::bind(&IRender::OnCameraUpdate, this, std::placeholders::_1));
}

void IRender::OnCameraUpdate(CameraRenderEvent& rEvent)
{
	UpdateProjCamera(rEvent.m_pTargetCamera);
}

void ZG::IRender::SetDepthBuffer(DepthBuffer* pDepthBuffer)
{

}
