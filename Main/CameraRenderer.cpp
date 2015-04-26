#include "stdafx.h"
#include "CameraRenderer.h"
#include "RasterCamera.h"
#include "World.h"
#include "ResourceManager.h"
#include "MaterialResource.h"
#include "RasterMaterial.h"
#include "RenderSystem.h"
#include "RenderView.h"
#include "EnviromentSetting.h"

CameraRenderer::CameraRenderer()
	: m_pWorld(nullptr)
	, m_pRender(nullptr)
	, m_pTarget(nullptr)
	, m_bClearColor(true)
	, m_bClearDepth(true)
	, m_fDepth(1.0f)
	, m_clrColr(GameColor::blue)
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
	//m_pRender->SetRenderTarget(0,m_pTarget);
	m_pRender->ClearTarget(m_bClearColor, m_clrColr, m_bClearDepth, m_fDepth);


	IRenderTarget* pTarget = nullptr;
	if (EnviromentSetting::GetInstance()->GetIntSetting("HDR") == true)
	{
		pTarget = m_pRender->m_pRenderSystem->GetDefaultRenderTarget();
	}
	else
	{
		pTarget = m_pRender->m_pRenderSystem->GetActiveRenderView();
	}
	m_pRender->Render(pCamera, m_pWorld,pTarget);

	shared_ptr<RasterMaterial> mat = dynamic_pointer_cast<RasterMaterial>(ResourceManager<MaterialResource>::GetInstance()->GetResource("./data/material/builtin/quad.smat.xml"));


	if (EnviromentSetting::GetInstance()->GetIntSetting("HDR") == true)
	{
		m_pRender->DrawScreen(m_pRender->m_pRenderSystem->GetDefaultRenderTarget(), m_pRender->m_pRenderSystem->GetActiveRenderView(), mat);
	}
	
}

void CameraRenderer::UpdateMatrix(CameraBase* pCamera)
{
	m_pRender->UpdateProjCamera(pCamera);
}
