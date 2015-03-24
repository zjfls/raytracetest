#include "stdafx.h"
#include "CameraBase.h"
#include "IRender.h"
#include "IWorld.h"
#include "RenderManager.h"
#include "RenderView.h"
#include "RenderSystem.h"


CameraBase::CameraBase()
{
	m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	m_pRenderTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
}


CameraBase::~CameraBase()
{
}

void CameraBase::Render()
{
	m_pRender->SetRenderTarget(m_pRenderTarget);
	m_pRender->m_pCurrentRenderCamera = this;
}

void CameraBase::Update()
{
	UpdateMatrix();
}

void CameraBase::OnLateUpdate()
{
	m_pRender->Render(this,IWorld::pSingleWorld);
}
void CameraBase::UpdateMatrix()
{

}