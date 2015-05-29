#pragma once
#include "RenderEnum.h"
struct stRenderViewInfo;
class IRender;
class RenderView;
class RenderPath;
class RasterRender;

class HardwareVertexShader;
class HardwareFragShader;
class VertexShaderDesc;
class FragShaderDesc;
class HardwareVertexBuffer;
class HardwareIndexBuffer;
class IndexData;
class MeshVertexData;
class HardwareTexture;
class Texture;
class IRenderTarget;
class VertexData;
class MAIN_API RenderSystem
{
public:
	virtual ~RenderSystem();
	RasterRender* GetDefaultRender() const;
	RenderView* GetDefaultRenderView() const;
	IRenderTarget* GetDefaultRenderTarget() const;




	virtual bool					InitRenderSystem(const stRenderViewInfo& viewInfo) = 0;
	virtual HardwareVertexShader*	GetHardwareVertexShader(const VertexShaderDesc& vertexShaderDesc) = 0;
	virtual HardwareFragShader*		GetHardwareFragShader(const FragShaderDesc& fragShaderDesc) = 0;
	virtual HardwareVertexBuffer*	GetHardwareVertexBuffer(VertexData* pData) = 0;
	virtual HardwareIndexBuffer*	GetHardwareIndexBuffer(IndexData* pData) = 0;
	virtual HardwareTexture*		GetHardwareTexture(shared_ptr<Texture> pTexture) = 0;
	virtual IRenderTarget*			CreateRenderTarget(unsigned int nWidth, unsigned int nHeight, TARGETFORMAT eTarget, EMULTISAMPLETYPE eMultiSample,unsigned int nQuality) = 0;
	virtual RenderView*				CreateRenderView(stRenderViewInfo& renderViewInfo) = 0;
	virtual bool					OnFrameBegin() = 0;
	virtual void					OnFrameEnd() = 0;
	virtual void					ReleaseRenderTarget(IRenderTarget* pTarget);
	//shared_ptr<

	RenderView*						GetActiveRenderView(){ return m_pActiveView; };
	void							SetActiveRenderView(RenderView* pView){ m_pActiveView = pView; };
protected:
	const char*			GetVertexShaderCode(const VertexShaderDesc& vertexShaderDesc);
	const char*			GetFragShaderCode(const FragShaderDesc& fragShaderDesc);
	string				GenerateVertexShaderDescString(const VertexShaderDesc& vertexShaderDesc);
	string				GenerateFragShaderDescString(const FragShaderDesc& fragShaderDesc);

protected:
	virtual void	CreateDefaultRender(const RenderPath* pPath) = 0;
	void	InitRender(RasterRender* pRender);
	std::unordered_map<string, HardwareVertexShader*> m_mapHardwareVertexShader;
	std::unordered_map<string, HardwareFragShader*> m_mapHardwareFragShader;
	std::unordered_map<IndexData*, HardwareIndexBuffer*> m_IndexDataMap;
	std::unordered_map<VertexData*, HardwareVertexBuffer*> m_VertexDataMap;
	std::unordered_map<string, HardwareTexture*> m_mapTexture;


	//std::unordered_map<VertexShaderDesc, const char*> m_VertexShaderCode;
	std::vector<IRenderTarget*> m_vecRenderTarget;
	RasterRender* m_pDefaultRender;
	RenderView* m_pDefaultRenderView;
	IRenderTarget*	m_pDefaultRenderTarget;
	RenderView*	m_pActiveView;
	RenderSystem();
	friend class RenderManager;
};

