#include "stdafx.h"
#include "CameraBase.h"
#include "IRender.h"
#include "IWorld.h"
#include "RenderManager.h"
#include "RenderView.h"


CameraBase::CameraBase()
{
	m_pRender = RenderManager::GetInstance()->GetDefaultRender();
	m_pRenderTarget = RenderManager::GetInstance()->GetDefaultRenderView();
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
	
}

void CameraBase::OnLateUpdate()
{
	m_pRender->Render(this,IWorld::pSingleWorld);
}
