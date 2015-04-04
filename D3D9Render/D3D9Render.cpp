#include "stdafx.h"
#include "D3D9Render.h"
#include "VertexData.h"
#include "IndexData.h"
#include "D3D9VertexBuffer.h"
#include "D3D9IndexBuffer.h"
#include "D3D9RenderSystem.h"
#include "D3D9VertexShader.h"
#include "D3D9FragShader.h"
#include "D3D9Texture2D.h"
#include "CameraBase.h"

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
	D3D9VertexShader* pD3D9Shader = dynamic_cast<D3D9VertexShader*>(pVertexShader);
	if (pD3D9Shader == nullptr)
	{
		return false;
	}

	if (FAILED(m_pDevice->SetVertexShader(pD3D9Shader->m_pVertexShader)))
	{
		return false;
	}
	return true;
}

bool D3D9Render::SetFragShader(HardwareFragShader* pFragShader)
{
	D3D9FragShader* pD3D9Shader = dynamic_cast<D3D9FragShader*>(pFragShader);
	if (pD3D9Shader == nullptr)
	{
		return false;
	}
	if (FAILED(m_pDevice->SetPixelShader(pD3D9Shader->m_pFragShader)))
	{
		return false;
	}
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
		//m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_pDevice->SetRenderState(D3DRS_ZENABLE, true);
		m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		m_pDevice->SetIndices(pD3DIndexBuff->m_pIndexBuffer);
		m_pDevice->SetVertexDeclaration(pD3DVertexBuff->m_pVertexDecal);
		m_pDevice->SetStreamSource(0, pD3DVertexBuff->m_pVertexBuffer, 0, pVertexBuff->m_nStrip);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pD3DVertexBuff->m_nNumVertex, 0, pD3DIndexBuff->m_nIndexNum / 3);
	}
}

bool D3D9Render::SetTexture(int nSamplerID, HardwareTexture* pTexture)
{
	D3D9Texture2D* p2DTex = dynamic_cast<D3D9Texture2D*>(pTexture);
	if (pTexture != nullptr)
	{
		m_pDevice->SetTexture(nSamplerID, p2DTex->m_pTexture);
		return true;
	}
	return false;
}

void D3D9Render::UpdateProjCamera(CameraBase* pCamera)
{
	float fovy, aspect, zn, zf;
	fovy = pCamera->m_fFovy;
	aspect = pCamera->m_fAspect;
	zn = pCamera->m_fNear;
	zf = pCamera->m_fFar;
	
	float yScale = 1/tan(fovy / 2);
	float xScale = yScale / aspect;
	pCamera->m_MatProj = Matrix44(
		xScale, 0, 0, 0,
		0, yScale, 0, 0,
		0, 0, zf / (zf - zn), 1,
		0, 0, -zn*zf / (zf - zn), 0);
}

//
bool D3D9Render::SetRenderStateCollection(const RenderStateCollection& stateCollection)
{
	return true;
}

bool D3D9Render::SetBlendEnable(bool b)
{
	return true;
}

bool D3D9Render::SetBlendSrc(EALPHABLEND eBlend)
{
	return true;
}

bool D3D9Render::SetBlendDst(EALPHABLEND eBlend)
{
	return true;
}

bool D3D9Render::SetZTestEnable(bool b)
{
	return true;
}

bool D3D9Render::SetZWriteEnable(bool b)
{
	return true;
}

bool D3D9Render::SetZFunc(ERENDERCMPFUNC eCmp)
{
	return true;
}

bool D3D9Render::SetAlphaTest(bool b)
{
	return true;
}

bool D3D9Render::SetAlphaFunc(ERENDERCMPFUNC eCmp)
{
	return true;
}

bool D3D9Render::SetAlphaTestFactor(float f)
{
	return true;
}

bool D3D9Render::SetCullMode(ERENDERCULL eCull)
{
	return true;
}

bool D3D9Render::RenderBegin()
{
	if (FAILED(m_pDevice->BeginScene()))
	{
		return false;
	}

	////
	//float vertices[] =
	//{
	//	-10.0f, 0.0f, 0.f, // x, y, z, rhw, color
	//	0.0f, 0.0f, 115.0f,
	//	10.0f, 0.0f, 0.0f
	//};
	//m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, &vertices, 12);



	return true;
}

bool D3D9Render::RenderEnd()
{
	if (FAILED(m_pDevice->EndScene()))
	{
		return false;
	}
	return true;
}

bool D3D9Render::ClearTarget(bool bClearColor, Color clr, bool bClearDepth /*= true*/, float fDepth /*= 1.0f*/)
{
	DWORD CLSFLG = 0;
	if (bClearColor)
	{
		CLSFLG |= D3DCLEAR_TARGET;
	}
	if (bClearDepth)
	{
		CLSFLG |= D3DCLEAR_ZBUFFER;
	}
	D3DXCOLOR clrColor = D3DCOLOR_ARGB(int(clr.m_fA * 255), int(clr.m_fR * 255), int(clr.m_fG * 255), int(clr.m_fB * 255));
	if (FAILED(m_pDevice->Clear(0, nullptr, CLSFLG, clrColor, fDepth, 0)))
	{
		return false;
	}
	return true;
}
