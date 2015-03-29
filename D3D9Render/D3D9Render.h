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
	//static D3D9Render* create(void* pArg);


	IDirect3DDevice9Ex*	m_pDevice;
};

