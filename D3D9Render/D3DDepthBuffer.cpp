#include "stdafx.h"
#include "D3DDepthBuffer.h"
#include <d3d9.h>
#include "RenderManager.h"
#include "D3D9RenderView.h"
#include "RenderSystem.h"


ZG::D3DDepthBuffer::D3DDepthBuffer()
	:m_pDepthSurface(nullptr)
{

}

ZG::D3DDepthBuffer::~D3DDepthBuffer()
{
	SAFE_RELEASE(m_pDepthSurface);
}

void ZG::D3DDepthBuffer::OnDeviceLost()
{
	SAFE_RELEASE(m_pDepthSurface);

}

void ZG::D3DDepthBuffer::OnDeviceReset()
{
	//
	D3D9RenderView* pRenderView = dynamic_cast<D3D9RenderView*>(RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView());
	if (pRenderView->m_DepthBuffer == this)
	{
		//
		m_pD3DDevice->GetDepthStencilSurface(&m_pDepthSurface);
		//
		return;
	}

	//
	D3DFORMAT d3dFormat;
	switch (m_nDepth)
	{
		case 16:
		{
			d3dFormat = D3DFMT_D16;
		}
		break;
		case 24:
		{
			d3dFormat = D3DFMT_D24S8;
		}
		break;
		default:
		break;
	}
	HRESULT hr = m_pD3DDevice->CreateDepthStencilSurface(m_nWidth, m_nHeight, d3dFormat, D3DMULTISAMPLE_NONE, 0, true, &m_pDepthSurface, nullptr);
	if (hr != S_OK)
	{
		std::cout << "reset depth buffer failed" << std::endl;
	}
}

bool ZG::D3DDepthBuffer::Resize(int nWidth, int nHeight)
{
	if (nWidth == 0 || nWidth == nHeight)
	{
		return true;
	}
	if (m_nWidth == nWidth && m_nHeight == nHeight)
	{
		return true;
	}
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	//
	D3D9RenderView* pRenderView = dynamic_cast<D3D9RenderView*>(RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView());
	SAFE_RELEASE(m_pDepthSurface);
	if (pRenderView->m_DepthBuffer == this)
	{
		//
		m_pD3DDevice->GetDepthStencilSurface(&m_pDepthSurface);
		//
		return true;
	}
	//
	//
	D3DFORMAT d3dFormat;
	switch (m_nDepth)
	{
		case 16:
		{
			d3dFormat = D3DFMT_D16;
		}
		break;
		case 24:
		{
			d3dFormat = D3DFMT_D24S8;
		}
		break;
		default:
		break;
	}
	m_pD3DDevice->CreateDepthStencilSurface(m_nWidth, m_nHeight, d3dFormat, D3DMULTISAMPLE_NONE, 0, true, &m_pDepthSurface, nullptr);
	if (m_pDepthSurface == nullptr)
	{
		std::cout << "create Depth Stencil Failed!" << std::endl;
	}
	return true;
}


