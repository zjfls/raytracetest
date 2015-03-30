#include "stdafx.h"
#include "CameraBase.h"
//#include "IRender.h"
#include "IWorld.h"
#include "IWorldObj.h"
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
	Matrix44 mat44 = m_pOwnerObj->m_pTransform->GetWorldMatrix();
	Vector3 eye = m_pOwnerObj->m_pTransform->GetWorldTranslate();
	Vector3 xaxis, yaxis, zaxis;
	xaxis = Vector3(mat44.M[0][0], mat44.M[0][1], mat44.M[0][2]);
	yaxis = Vector3(mat44.M[1][0], mat44.M[1][1], mat44.M[1][2]);
	zaxis = Vector3(mat44.M[2][0], mat44.M[2][1], mat44.M[2][2]);
	//
	m_MatView = {
		xaxis.m_fx, yaxis.m_fx, zaxis.m_fx, 0,
		xaxis.m_fy, yaxis.m_fy, zaxis.m_fy, 0,
		xaxis.m_fz, yaxis.m_fz, zaxis.m_fz, 0,
		-xaxis.dot(eye), -yaxis.dot(eye), -zaxis.dot(eye), 1 };
	m_MatInverseView = {
		xaxis.m_fx, xaxis.m_fy, xaxis.m_fz, 0,
		yaxis.m_fx, yaxis.m_fy, yaxis.m_fz, 0,
		zaxis.m_fx, zaxis.m_fy, zaxis.m_fz, 0,
		eye.m_fx, eye.m_fy, eye.m_fz, 1
	};

	m_MatViewProj = m_MatView * m_MatProj;
}

ModuleBase* CameraBase::Clone()
{
	CameraBase* pCamera = new CameraBase;
	pCamera->m_fAspect = m_fFovy;
	pCamera->m_fFovy = m_fAspect;
	return pCamera;
}
