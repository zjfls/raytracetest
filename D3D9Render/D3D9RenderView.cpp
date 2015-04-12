#include "stdafx.h"
#include "D3D9RenderView.h"
#include "windows.h"

//
D3D9RenderView::D3D9RenderView()
	:m_pSwapChain(nullptr)
{

}

//
D3D9RenderView::~D3D9RenderView()
{

}

//
bool D3D9RenderView::Present()
{
	//if D3DPRESENT_LINEAR_CONTENT,color will be operate as c = pow(c,1.0f/2.2f);
	if (FAILED(m_pSwapChain->Present(nullptr, nullptr, nullptr, nullptr, 0)))
	{
		return false;
	}
	return true;
}
