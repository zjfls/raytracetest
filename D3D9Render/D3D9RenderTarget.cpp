#include "stdafx.h"
#include "D3D9RenderTarget.h"
#include "d3d9.h"
#include "D3D9RenderSystem.h"
#include "DepthBuffer.h"
#include "RenderView.h"

D3D9RenderTarget::D3D9RenderTarget()
{
}


D3D9RenderTarget::~D3D9RenderTarget()
{
}

void D3D9RenderTarget::OnDeviceLost()
{
	SAFE_RELEASE(m_pSurfTexture);
}

void D3D9RenderTarget::OnDeviceReset()
{
	//D3D9RenderTarget* pTarget = new D3D9RenderTarget;
	D3DFORMAT d3dFormat = D3D9RenderSystem::getBufferFormat(m_eTargetFormt);
	IDirect3DTexture9* pTexture;
	if (D3D_OK != m_pD3DDevice->CreateTexture(m_nWidth, m_nHeight, 1, D3DUSAGE_RENDERTARGET, d3dFormat, D3DPOOL_DEFAULT, &pTexture, nullptr))
	{
		std::cout << "create rendertarget texture failed!" << std::endl;
	}
	//
	//pTarget->m_nWidth = nWidth;
	//pTarget->m_nHeight = nHeight;
	//pTarget->m_eTargetFormt = eTarget;
	//
	//pTexture->GetSurfaceLevel(0, &pTarget->m_pSurface);
	m_pSurfTexture = pTexture;
}

bool ZG::D3D9RenderTarget::Resize(int nWidth, int nHeight)
{
	//std::cout << "resize:" << nWidth << " " << nHeight << std::endl;
	if (nWidth == 0 || nHeight == 0)
	{
		return true;
	}
	if (nWidth == m_nWidth && nHeight == m_nHeight)
	{
		return true;
	}
	SAFE_RELEASE(m_pSurfTexture);
	D3DFORMAT d3dFormat = D3D9RenderSystem::getBufferFormat(m_eTargetFormt);
	IDirect3DTexture9* pTexture;
	//
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	if (D3D_OK != m_pD3DDevice->CreateTexture(m_nWidth, m_nHeight, 1, D3DUSAGE_RENDERTARGET, d3dFormat, D3DPOOL_DEFAULT, &pTexture, nullptr))
	{
		std::cout << "create rendertarget texture failed!" << std::endl;
	}


	m_pSurfTexture = pTexture;
	//
	if (nWidth != m_DepthBuffer->m_nWidth || nHeight != m_DepthBuffer->m_nHeight)
	{
		m_DepthBuffer->Resize(nWidth, nHeight);
	}
	//
	return true;
}
