#include "stdafx.h"
#include "CameraRenderer.h"
#include "RasterCamera.h"
#include "World.h"

CameraRenderer::CameraRenderer()
	: m_pWorld(nullptr)
	, m_pRender(nullptr)
	, m_pTarget(nullptr)
{
}


CameraRenderer::~CameraRenderer()
{
}

void CameraRenderer::OnNotify(string msg, IListenerSubject* pSubject)
{

	RasterCamera* pCamera = dynamic_cast<RasterCamera*>(pSubject);
	if (msg == "Render")
	{
		Render(pCamera);
	}
	if (msg == "UpdateMatrix")
	{
		UpdateMatrix(pCamera);
	}
}

void CameraRenderer::Render(CameraBase* pCamera)
{
	if (m_pRender == nullptr || m_pTarget == nullptr || m_pWorld == nullptr || pCamera == nullptr)
	{
		return;
	}
	m_pRender->m_pCurrentRenderCamera = pCamera;
	m_pRender->SetRenderTarget(m_pTarget);
	m_pRender->Render(pCamera, m_pWorld);
}

void CameraRenderer::UpdateMatrix(CameraBase* pCamera)
{
	m_pRender->UpdateProjCamera(pCamera);
}