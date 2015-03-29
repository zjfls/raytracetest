#include "stdafx.h"
#include "CameraBase.h"
//#include "IRender.h"
#include "IWorld.h"
//#include "RenderManager.h"
//#include "RenderView.h"
//#include "RenderSystem.h"


CameraBase::CameraBase()
{
	//m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	//m_pRenderTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
}


CameraBase::~CameraBase()
{
}

void CameraBase::Render()
{
	//m_pRender->SetRenderTarget(m_pRenderTarget);
	//m_pRender->m_pCurrentRenderCamera = this;
	//m_pRender->Render(this, IWorld::pSingleWorld);
	NotifyListener("Render", this);
}

void CameraBase::Update()
{
	NotifyListener("UpdateMatrix", this);
	UpdateMatrix();
}

void CameraBase::OnLateUpdate()
{
	Render();
}
void CameraBase::UpdateMatrix()
{

}

ModuleBase* CameraBase::Clone()
{
	CameraBase* pCamera = new CameraBase;
	pCamera->m_fAspect = m_fFovy;
	pCamera->m_fFovy = m_fAspect;
	return pCamera;
}
