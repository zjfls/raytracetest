#pragma once
#include "RenderSystem.h"
#include "d3d9.h"
#include "RenderEnum.h"
class RasterRender;
class D3D9RenderSystem :
	public RenderSystem
{
public:	
	virtual ~D3D9RenderSystem();



	virtual bool InitRenderSystem(const stRenderViewInfo& viewInfo);
	virtual HardwareVertexShader* GetHardwareVertexShader(const VertexShaderDesc& vertexShaderDesc);
	virtual HardwareFragShader* GetHardwareFragShader(const FragShaderDesc& fragShaderDesc);
	virtual HardwareVertexBuffer* GetHardwareVertexBuffer(VertexData* pData);
	virtual HardwareIndexBuffer*	GetHardwareIndexBuffer(IndexData* pData);
	
	D3DSWAPEFFECT getSwapEffect(const EBUFFSWARP eSwap) const;
	D3DFORMAT		getBufferFormat(const TARGETFORMAT eFormat) const;
protected:
	D3D9RenderSystem();
	virtual void	CreateDefaultRender(const RenderPath* pPath);
	friend class RenderManager;

	RenderView*		m_pDefaultRenderView;
	RasterRender*	m_pDefaultRender;
	LPDIRECT3D9EX             m_pD3D;
	LPDIRECT3DDEVICE9EX		m_pD3DDevice;
};

