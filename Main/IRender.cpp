#include "stdafx.h"
#include "IRender.h"


IRender::IRender()
	:m_pCurrentRenderCamera(nullptr)
{
}


IRender::~IRender()
{
}

void IRender::SetRenderTarget(IRenderTarget* pTarget)
{

}



void IRender::SetCurrentRenderCamera(CameraBase* pCamera)
{
	m_pCurrentRenderCamera = pCamera;
}
