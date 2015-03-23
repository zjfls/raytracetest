#pragma once
#include "RenderSystem.h"
#include "d3d9.h"
#include "RenderEnum.h"
class D3D9RenderSystem :
	public RenderSystem
{
public:	
	virtual ~D3D9RenderSystem();
	virtual bool InitRenderSystem(const stRenderViewInfo& viewInfo) const;
	virtual IRender* GetDefaultRender() const;
	virtual RenderView* GetDefaultRenderView() const;
	virtual HardwareVertexShader* GetHardwareVertexShader(const VertexShaderDesc& vertexShaderDesc) const;
	virtual HardwareFragShader* GetHardwareFragShader(const FragShaderDesc& fragShaderDesc) const;
	
	D3DSWAPEFFECT getSwapEffect(const EBUFFSWARP eSwap) const;
	D3DFORMAT		getBufferFormat(const TARGETFORMAT eFormat) const;
protected:
	D3D9RenderSystem();
	virtual void	CreateDefaultRender(const RenderPath* pPath) const;
	friend class RenderManager;
};

