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
	if (FAILED(m_pSwapChain->Present(nullptr, nullptr, nullptr, nullptr, D3DPRESENT_LINEAR_CONTENT)))
	{
		return false;
	}
	return true;
}
