#include "stdafx.h"
#include "IRender.h"


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



void IRender::SetCurrentRenderCamera(shared_ptr<CameraBase> pCamera)
{
	m_pCurrentRenderCamera = pCamera;
}
