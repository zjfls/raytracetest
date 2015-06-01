#pragma once
#include "RenderEnum.h"
#include "GameObjectBase.h"
namespace ZG
{
	class VertexDataEventArg;
	class IndexDataEventArg;
}

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
class MAIN_API RenderSystem:public ZG::GameObjectBase
{
public:
	virtual ~RenderSystem();
	RasterRender* GetDefaultRender() const;
	RenderView* GetDefaultRenderView() const;
	IRenderTarget* GetDefaultRenderTarget() const;




	virtual bool					InitRenderSystem( stRenderViewInfo& viewInfo) = 0;
	virtual HardwareVertexShader*	GetHardwareVertexShader( VertexShaderDesc& vertexShaderDesc) = 0;
	virtual HardwareFragShader*		GetHardwareFragShader( FragShaderDesc& fragShaderDesc) = 0;
	virtual HardwareVertexBuffer*	GetHardwareVertexBuffer(VertexData* pData) = 0;
	virtual HardwareIndexBuffer*	GetHardwareIndexBuffer(IndexData* pData) = 0;
	virtual HardwareTexture*		GetHardwareTexture(SmartPointer<Texture> pTexture) = 0;
	virtual IRenderTarget*			CreateRenderTarget(unsigned int nWidth, unsigned int nHeight, TARGETFORMAT eTarget, EMULTISAMPLETYPE eMultiSample,unsigned int nQuality) = 0;
	virtual RenderView*				CreateRenderView(stRenderViewInfo& renderViewInfo) = 0;
	virtual bool					OnFrameBegin() = 0;
	virtual void					OnFrameEnd() = 0;
	virtual void					ReleaseRenderTarget(IRenderTarget* pTarget);
	//SmartPointer<

	RenderView*						GetActiveRenderView(){ return m_pActiveView; };
	void							SetActiveRenderView(RenderView* pView){ m_pActiveView = pView; };
	//
	//
	void							OnVertexDataDelete(ZG::VertexDataEventArg& e);
	void							OnIndexDataDelete(ZG::IndexDataEventArg& e);
protected:
	const char*			GetVertexShaderCode(VertexShaderDesc& vertexShaderDesc);
	const char*			GetFragShaderCode(FragShaderDesc& fragShaderDesc);
	string				GenerateVertexShaderDescString(VertexShaderDesc& vertexShaderDesc);
	string				GenerateFragShaderDescString(FragShaderDesc& fragShaderDesc);

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

