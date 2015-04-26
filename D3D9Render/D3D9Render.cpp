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
#include "D3D9RenderTarget.h"
#include "D3D9RenderView.h"
#include "FragShader.h"
#include "RasterMaterial.h"
#include "RenderPass.h"
#include "VertexShader.h"
#include "EnviromentSetting.h"
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
		m_pDevice->SetVertexDeclaration(pD3DVertexBuff->m_pVertexBuffDecal->m_pVertexDecal);
		m_pDevice->SetStreamSource(0, pD3DVertexBuff->m_pVertexBuffer, 0, pVertexBuff->m_nStrip);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pD3DVertexBuff->m_nNumVertex / 3);
	}
	else
	{
		//m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		//m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		//m_pDevice->SetRenderState(D3DRS_ZENABLE, true);
		//m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		//m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		m_pDevice->SetIndices(pD3DIndexBuff->m_pIndexBuffer);
		m_pDevice->SetVertexDeclaration(pD3DVertexBuff->m_pVertexBuffDecal->m_pVertexDecal);
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
		m_pDevice->SetSamplerState(nSamplerID, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pDevice->SetSamplerState(nSamplerID, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_pDevice->SetSamplerState(nSamplerID, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		//m_pDevice->SetSamplerState(nSamplerID, D3DSAMP_SRGBTEXTURE, 1.0);
		return true;
	}
	else
	{
		m_pDevice->SetTexture(nSamplerID, nullptr);
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
	if (D3D_OK != m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, b))
	{
		return false;
	}
	return true;
}

bool D3D9Render::SetBlendSrc(EALPHABLEND eBlend)
{
	D3DBLEND blend = GetD3DBlendType(eBlend);
	if (D3D_OK != m_pDevice->SetRenderState(D3DRS_SRCBLEND, blend))
	{
		return false;
	}
	return true;
}

bool D3D9Render::SetBlendDst(EALPHABLEND eBlend)
{
	D3DBLEND blend = GetD3DBlendType(eBlend);
	if (D3D_OK != m_pDevice->SetRenderState(D3DRS_DESTBLEND, blend))
	{
		return false;
	}
	return true;
}

bool D3D9Render::SetZTestEnable(bool b)
{
	if (D3D_OK != m_pDevice->SetRenderState(D3DRS_ZENABLE, b))
	{
		return false;
	}
	return true;
}

bool D3D9Render::SetZWriteEnable(bool b)
{
	if (D3D_OK != m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, b))
	{
		return false;
	}
	return true;
}

bool D3D9Render::SetZFunc(ERENDERCMPFUNC eCmp)
{
	_D3DCMPFUNC eFunc = D3DCMP_ALWAYS;
	switch (eCmp)
	{
		case RENDERCMP_NEVER:
		break;
		case RENDERCMP_LESS:
		eFunc = D3DCMP_LESS;
		break;
		case RENDERCMP_EQUAL:
		break;
		case RENDERCMP_LESSEQUAL:
		eFunc = D3DCMP_LESSEQUAL;
		break;
		case RENDERCMP_GREATER:
		break;
		case RENDERCMP_NOTEQUAL:
		break;
		case RENDERCMP_GREATEREQUAL:
		break;
		case RENDERCMP_ALWAYS:
		break;
		default:
		return false;
		break;
	}
	if (D3D_OK != m_pDevice->SetRenderState(D3DRS_ZFUNC, eFunc))
	{
		return false;
	}
	return true;
}

bool D3D9Render::SetAlphaTest(bool b)
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, b);
	return true;
}

bool D3D9Render::SetAlphaFunc(ERENDERCMPFUNC eCmp)
{
	switch (eCmp)
	{
		case RENDERCMP_GREATER:
		{
			m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		}
		break;
		case RENDERCMP_LESS:
		{
			m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_LESS);
		}
		break;
	}
	return true;
}

bool D3D9Render::SetAlphaTestFactor(int f)
{
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, f);
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

D3DBLEND D3D9Render::GetD3DBlendType(EALPHABLEND eBlend)
{
	switch (eBlend)
	{
		case BLEND_ZERO:
		return D3DBLEND_ZERO;
		break;
		case BLEND_ONE:
		return D3DBLEND_ONE;
		break;
		case BLEND_SRCCOLOR:
		return D3DBLEND_SRCCOLOR;
		break;
		case BLEND_INVSRCCOLOR:
		return D3DBLEND_INVSRCCOLOR;
		break;
		case BLEND_SRCALPHA:
		return D3DBLEND_SRCALPHA;
		break;
		case BLEND_INVSRCALPHA:
		return D3DBLEND_INVSRCCOLOR;
		break;
		case BLEND_DESTALPHA:
		return D3DBLEND_DESTALPHA;
		break;
		case BLEND_DESTCOLOR:
		return D3DBLEND_DESTCOLOR;
		break;
		case BLEND_INVDESTCOLOR:
		return D3DBLEND_INVDESTCOLOR;
		break;
		default:
		break;
	}
}

bool D3D9Render::SetSamplerSRGB(unsigned int nIndex, unsigned int SRGB)
{
	if (D3D_OK != m_pDevice->SetSamplerState(nIndex, D3DSAMP_SRGBTEXTURE, SRGB))
	{
		return false;
	}
	return true;
}

void D3D9Render::SetRenderTarget(int nIndex, IRenderTarget* pTarget)
{
	RasterRender::SetRenderTarget(nIndex,pTarget);
	IDirect3DSurface9* pSurface = nullptr;
	D3D9RenderView* pView = dynamic_cast<D3D9RenderView*>(pTarget);
	if (pView != nullptr && pView->m_pSwapChain != nullptr)
	{
		pView->m_pSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	}
	D3D9RenderTarget* pD3DTarget = dynamic_cast<D3D9RenderTarget*>(nIndex,pTarget);
	//
	if (pD3DTarget != nullptr)
	{
		pD3DTarget->m_pSurfTexture->GetSurfaceLevel(0, &pSurface);
	}

	if (pSurface != nullptr)
	{
		m_pDevice->SetRenderTarget(nIndex, pSurface);
		pSurface->Release();
	}	
}

void D3D9Render::DrawScreen(IRenderTarget* pSource, IRenderTarget* pTarget, shared_ptr<RasterMaterial> pMat /*= nullptr*/)
{
	float arrayScreen[] = 
	{
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,

		
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	m_pDevice->SetFVF(D3DFVF_XYZ);
	FragShaderDesc fragDesc;
	fragDesc.m_pFragShader = pMat->m_RenderPassMap.begin()->second->m_pFragShader;
	fragDesc.m_eFragShaderDesc = EFRAGSHADERORIGIN;
	HardwareFragShader* pfragshader = m_pRenderSystem->GetHardwareFragShader(fragDesc);
	VertexShaderDesc vertDesc;
	vertDesc.m_pVertexShader = pMat->m_RenderPassMap.begin()->second->m_pVertexShader;
	vertDesc.m_eVShaderDesc = EVERTEXSHADERORIGIN;
	HardwareVertexShader* pVertexShader = m_pRenderSystem->GetHardwareVertexShader(vertDesc);
	SetVertexShader(pVertexShader);
	SetFragShader(pfragshader);
	SetZTestEnable(false);
	SetAlphaTest(false);
	SetRenderTarget(0,pTarget);
	D3D9RenderTarget* pD3DRenderTarget = (D3D9RenderTarget*)pSource;
	ShaderConstantInfo info = pfragshader->m_mapConstants["sourceTex"];
	m_pDevice->SetTexture(0, pD3DRenderTarget->m_pSurfTexture);
	if (EnviromentSetting::GetInstance()->GetIntSetting("LinearLighting") == true)
	{
		SetSamplerSRGB(info.m_nRegIndex, 1);
	}

	
	//
	
	//SetTexture(0, pD3DTex->m_pSurfTexture);

	

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, arrayScreen, 12);


	//m_pDevice->StretchRect()

}
