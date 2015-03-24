#include "stdafx.h"
#include "D3D9Render.h"
#include "VertexData.h"
#include "IndexData.h"
#include "D3D9VertexBuffer.h"
#include "D3D9IndexBuffer.h"
#include "D3D9RenderSystem.h"

D3D9Render::D3D9Render(const RenderPath* pPath)
	:RasterRender(pPath)
	, m_pDevice(nullptr)
{
}


D3D9Render::~D3D9Render()
{
}

bool D3D9Render::SetVertexShader(HardwareVertexShader* pVertexShader)
{
	return true;
}

bool D3D9Render::SetFragShader(HardwareFragShader* pFragShader)
{
	return true;
}

void D3D9Render::Render(HardwareIndexBuffer* pIndexBuff, HardwareVertexBuffer* pVertexBuff)
{
	D3D9VertexBuffer* pD3DVertexBuff = (D3D9VertexBuffer*)pVertexBuff;
	D3D9IndexBuffer* pD3DIndexBuff = (D3D9IndexBuffer*)pIndexBuff;
	if (pD3DVertexBuff == nullptr)
	{
		return;
	}
	if (pD3DIndexBuff == nullptr)
	{
		m_pDevice->SetVertexDeclaration(pD3DVertexBuff->m_pVertexDecal);
		m_pDevice->SetStreamSource(0, pD3DVertexBuff->m_pVertexBuffer, 0, pVertexBuff->m_nStrip);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pD3DVertexBuff->m_nNumVertex / 3);
	}
	else
	{
		m_pDevice->SetIndices(pD3DIndexBuff->m_pIndexBuffer);
		m_pDevice->SetVertexDeclaration(pD3DVertexBuff->m_pVertexDecal);
		m_pDevice->SetStreamSource(0, pD3DVertexBuff->m_pVertexBuffer, 0, pVertexBuff->m_nStrip);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pD3DVertexBuff->m_nNumVertex, 0, pD3DIndexBuff->m_nIndexNum / 3);
	}
}
