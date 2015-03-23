#include "stdafx.h"
#include "D3D9Render.h"
#include "D3D9Manager.h"


D3D9Render::D3D9Render(const RenderPath* pPath)
	:RasterRender(pPath)
{
}


D3D9Render::~D3D9Render()
{
}

//D3D9Render* D3D9Render::create(void* pArg)
//{
//	if (D3D9Manager::GetInstance()->m_pD3D == nullptr)
//	{
//		D3D9Manager::GetInstance()->CreateDevice();
//	}
//	D3D9Render* pRender = new D3D9Render;
//	return pRender;
//}
