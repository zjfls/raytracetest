#pragma once
#include "RenderSystem.h"
#include "d3d9.h"
#include "RenderEnum.h"
#include "VertexData.h"

class RasterRender;
class D3D9RenderSystem :
	public RenderSystem
{
public:	
	virtual ~D3D9RenderSystem();
	D3D9RenderSystem();


	virtual bool					InitRenderSystem(const stRenderViewInfo& viewInfo);
	virtual HardwareVertexShader*	GetHardwareVertexShader(const VertexShaderDesc& vertexShaderDesc);
	virtual HardwareFragShader*		GetHardwareFragShader(const FragShaderDesc& fragShaderDesc);
	virtual HardwareVertexBuffer*	GetHardwareVertexBuffer(VertexData* pData);
	virtual HardwareIndexBuffer*	GetHardwareIndexBuffer(IndexData* pData);
	virtual HardwareTexture*		GetHardwareTexture(shared_ptr<Texture> pTexture);
	
	D3DSWAPEFFECT getSwapEffect(const EBUFFSWARP eSwap) const;
	D3DFORMAT		getBufferFormat(const TARGETFORMAT eFormat) const;
private:
	IDirect3DVertexDeclaration9*	CreateVertexDeclarationFromDesc(std::vector<VertexData::VertexDataDesc>& vecDataDesc);
	D3DDECLTYPE						GetD3DDeclType(EnumVertexTypeDesc desc) const;
	BYTE							GetD3DDeclUsage(EnumVertexUseDesc desc) const;
protected:
	virtual void		CreateDefaultRender(const RenderPath* pPath);
	friend class RenderManager;


public:
	LPDIRECT3D9             m_pD3D;
	LPDIRECT3DDEVICE9		m_pD3DDevice;



};

