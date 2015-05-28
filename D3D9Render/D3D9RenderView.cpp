#include "stdafx.h"
#include "D3D9RenderView.h"
#include "windows.h"
#include "RenderManager.h"
#include "D3D9RenderSystem.h"
//
D3D9RenderView::D3D9RenderView()
	:m_pSwapChain(nullptr)
{

}

//
D3D9RenderView::~D3D9RenderView()
{
	SAFE_RELEASE(m_pSwapChain);
}

//
bool D3D9RenderView::Present()
{
	if (nullptr == m_pSwapChain)
	{
		return false;
	}
	//if D3DPRESENT_LINEAR_CONTENT,color will be operate as c = pow(c,1.0f/2.2f);
	if (FAILED(m_pSwapChain->Present(nullptr, nullptr, nullptr, nullptr, 0)))
	{
		return false;
	}
	return true;
}

void D3D9RenderView::OnDeviceLost()
{
	SAFE_RELEASE(m_pSwapChain);
	

}

void D3D9RenderView::OnDeviceReset()
{
	if (m_nIndex != 0)
	{
		//to do fix temp code
		int width = m_dpp.BackBufferWidth;
		int height = m_dpp.BackBufferHeight;
		m_dpp.BackBufferWidth = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView()->m_nWidth;
		m_dpp.BackBufferHeight = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView()->m_nHeight;
		HRESULT hr = m_pD3DDevice->CreateAdditionalSwapChain(&m_dpp, &m_pSwapChain);
		//Resize(width, height);
	}
	else
	{
		m_pD3DDevice->GetSwapChain(0, &m_pSwapChain);
	}
}

bool D3D9RenderView::Resize(int nX, int nY)
{
	m_nWidth = nX;
	m_nHeight = nY;
	m_dpp.BackBufferWidth = nX;
	m_dpp.BackBufferHeight = nY;
	SAFE_RELEASE(m_pSwapChain);
	//m_pSwapChain->Release();
	//m_pSwapChain = nullptr;
	HRESULT hr = m_pD3DDevice->CreateAdditionalSwapChain(&m_dpp, &m_pSwapChain);

	if (hr == D3D_OK)
	{
		std::cout << "resize view success!" << std::endl;
	}
	else
	{
		std::cout << "resize view failed!" << std::endl;
	}
	return true;
}



