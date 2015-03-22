#include "stdafx.h"
#include "D3D9Manager.h"
D3D9Manager* Singleton<D3D9Manager>::_instance = nullptr;
D3D9Manager::D3D9Manager()
	:m_pD3D(nullptr)
	, m_pD3DDevice(nullptr)
	, m_pDefaultRenderView(nullptr)
	, m_pDefaultRender(nullptr)
{

}


D3D9Manager::~D3D9Manager()
{

}

void D3D9Manager::CreateDevice()
{

}
