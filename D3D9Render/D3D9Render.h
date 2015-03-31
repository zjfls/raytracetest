#pragma once
#include "RasterRender.h"


struct IDirect3DDevice9Ex;
class D3D9Render :
	public RasterRender
{
public:
	D3D9Render(const RenderPath* pPath);
	virtual ~D3D9Render();
	virtual void Render(HardwareIndexBuffer* pIndexBuff, HardwareVertexBuffer* pVertexBuff);
	virtual bool SetVertexShader(HardwareVertexShader* pVertexShader);
	virtual bool SetFragShader(HardwareFragShader* pFragShader);
	virtual bool SetTexture(int nSamplerID, HardwareTexture* pTexture);
	virtual void UpdateProjCamera(CameraBase* pCamera);
	virtual bool SetRenderStateCollection(const RenderStateCollection& stateCollection);
	virtual bool SetBlendEnable(bool b);
	virtual bool SetBlendSrc(EALPHABLEND eBlend);
	virtual bool SetBlendDst(EALPHABLEND eBlend);
	virtual bool SetZTestEnable(bool b);
	virtual bool SetZWriteEnable(bool b);
	virtual bool SetZFunc(ERENDERCMPFUNC eCmp);
	virtual bool SetAlphaTest(bool b);
	virtual bool SetAlphaFunc(ERENDERCMPFUNC eCmp);
	virtual bool SetAlphaTestFactor(float f);
	virtual bool SetCullMode(ERENDERCULL eCull);
	virtual bool RenderBegin();
	virtual bool RenderEnd();

	IDirect3DDevice9Ex*	m_pDevice;
};

