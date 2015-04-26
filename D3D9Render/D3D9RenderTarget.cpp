#include "stdafx.h"
#include "D3D9RenderTarget.h"
#include "d3d9.h"
#include "D3D9RenderSystem.h"


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
