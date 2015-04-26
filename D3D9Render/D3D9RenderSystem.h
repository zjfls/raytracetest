#pragma once
#include "RenderSystem.h"
#include "d3d9.h"
#include "RenderEnum.h"
#include "VertexData.h"
#include "D3D9RenderTarget.h"

class stD3DVertexBuffDecal;
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
	virtual IRenderTarget*			CreateRenderTarget(unsigned int nWidth, unsigned int nHeight, TARGETFORMAT eTarget, EMULTISAMPLETYPE eMultiSample, unsigned int nQuality);
	virtual RenderView*				CreateRenderView(stRenderViewInfo& renderViewInfo);
	virtual bool					OnFrameBegin();
	virtual void					OnFrameEnd();

	static D3DSWAPEFFECT			getSwapEffect(const EBUFFSWARP eSwap);
	static D3DFORMAT				getBufferFormat(const TARGETFORMAT eFormat);
private:
	stD3DVertexBuffDecal*			CreateVertexDeclarationFromDesc(std::vector<VertexData::VertexDataDesc>& vecDataDesc);
	D3DDECLTYPE						GetD3DDeclType(EnumVertexTypeDesc desc) const;
	BYTE							GetD3DDeclUsage(EnumVertexUseDesc desc) const;
	stD3DVertexBuffDecal*			GetVertexDecal(std::vector<VertexData::VertexDataDesc>& decl);
protected:
	virtual void		CreateDefaultRender(const RenderPath* pPath);
	friend class RenderManager;



	std::vector<stD3DVertexBuffDecal*> m_VertexDecals;

	//std::vector<D3D9RenderTarget*> m_vecRenderTarget;
	//std::map<std::vector<D3DVERTEXELEMENT9>, IDirect3DVertexDeclaration9*> m_DecalMap;
	//std::vector<IDirect3DSwapChain9*> m_SwapChains;
public:
	LPDIRECT3D9             m_pD3D;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	D3DPRESENT_PARAMETERS	m_D3DPresentParamenter;






};

bool operator==(const std::vector<D3DVERTEXELEMENT9>& e1,const std::vector<D3DVERTEXELEMENT9>& e2);
bool operator<(const std::vector<D3DVERTEXELEMENT9>& e1,const std::vector<D3DVERTEXELEMENT9>& e2);


