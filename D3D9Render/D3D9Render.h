#pragma once
#include "RasterRender.h"
#include "Color.h"
#include "d3d9.h"

struct IDirect3DDevice9;
class D3D9Render :
	public RasterRender
{
public:
	D3D9Render(const RenderPath* pPath);
	virtual ~D3D9Render();



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void Render(HardwareIndexBuffer* pIndexBuff, HardwareVertexBuffer* pVertexBuff);
	virtual bool SetVertexShader(HardwareVertexShader* pVertexShader);
	virtual bool SetFragShader(HardwareFragShader* pFragShader);
	virtual bool SetTexture(int nSamplerID, HardwareTexture* pTexture);
	virtual void UpdateProjCamera(shared_ptr<CameraBase> pCamera);
	virtual bool SetRenderStateCollection(const RenderStateCollection& stateCollection);
	virtual bool SetBlendEnable(bool b);
	virtual bool SetBlendSrc(EALPHABLEND eBlend);
	virtual bool SetBlendDst(EALPHABLEND eBlend);
	virtual bool SetZTestEnable(bool b);
	virtual bool SetZWriteEnable(bool b);
	virtual bool SetZFunc(ERENDERCMPFUNC eCmp);
	virtual bool SetAlphaTest(bool b);
	virtual bool SetAlphaFunc(ERENDERCMPFUNC eCmp);
	virtual bool SetAlphaTestFactor(int f);
	virtual bool SetCullMode(ERENDERCULL eCull);
	virtual bool SetSamplerSRGB(unsigned int nIndex, unsigned int SRGB);
	virtual bool RenderBegin();
	virtual bool RenderEnd();
	virtual bool ClearTarget(bool bClearColor, GameColor clr, bool bClearDepth = true, float fDepth = 1.0f);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SetRenderTarget(int nIndex, IRenderTarget* pTarget);
	virtual void DrawScreen(IRenderTarget* pSource, IRenderTarget* pTarget, shared_ptr<RasterMaterial> pMat = nullptr);
	IDirect3DDevice9*	m_pDevice;
private:
	D3DBLEND GetD3DBlendType(EALPHABLEND eBlend);

};

