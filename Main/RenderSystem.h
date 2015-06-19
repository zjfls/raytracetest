#pragma once
#include "RenderEnum.h"
#include "GameObjectBase.h"
namespace ZG
{
	class VertexDataEventArg;
	class IndexDataEventArg;
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
	class DepthBuffer;
}


namespace ZG
{
	class MAIN_API RenderSystem :public ZG::GameObjectBase
	{
	public:
		virtual ~RenderSystem();
		RasterRender* GetDefaultRender();
		RenderView* GetDefaultRenderView() const;
		//IRenderTarget* GetDefaultRenderTarget() const;




		virtual bool					InitRenderSystem(stRenderViewInfo& viewInfo) = 0;
		virtual HardwareVertexShader*	GetHardwareVertexShader(VertexShaderDesc& vertexShaderDesc) = 0;
		virtual HardwareFragShader*		GetHardwareFragShader(FragShaderDesc& fragShaderDesc) = 0;
		virtual HardwareVertexBuffer*	GetHardwareVertexBuffer(VertexData* pData) = 0;
		virtual HardwareIndexBuffer*	GetHardwareIndexBuffer(IndexData* pData) = 0;
		virtual HardwareTexture*		GetHardwareTexture(SmartPointer<Texture> pTexture) = 0;
		virtual IRenderTarget*			CreateRenderTarget(unsigned int nWidth, unsigned int nHeight, TARGETFORMAT eTarget, EMULTISAMPLETYPE eMultiSample, unsigned int nQuality, int nDepth = 0) = 0;
		virtual RenderView*				CreateRenderView(stRenderViewInfo& renderViewInfo, int nDepth = 0) = 0;
		virtual DepthBuffer*			CreateDepthBuffer(int nWidth, int nHeight, int nDepth) = 0;
		virtual bool					OnFrameBegin() = 0;
		virtual void					OnFrameEnd() = 0;
		virtual void					ReleaseRenderTarget(IRenderTarget* pTarget);
		//SmartPointer<

		RenderView*						GetActiveRenderView(){ return m_pActiveView.get(); };
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
		std::unordered_map<string, SmartPointer<HardwareVertexShader>> m_mapHardwareVertexShader;
		std::unordered_map<string, SmartPointer<HardwareFragShader>> m_mapHardwareFragShader;
		std::unordered_map<IndexData*, HardwareIndexBuffer*> m_IndexDataMap;
		std::unordered_map<VertexData*, HardwareVertexBuffer*> m_VertexDataMap;
		std::unordered_map<string, HardwareTexture*> m_mapTexture;


		//std::unordered_map<VertexShaderDesc, const char*> m_VertexShaderCode;
		std::vector<SmartPointer<IRenderTarget>> m_vecRenderTarget;
		std::vector<SmartPointer<DepthBuffer>> m_vecDepthBuffer;
		SmartPointer<RasterRender> m_pDefaultRender;
		SmartPointer<RenderView> m_pDefaultRenderView;
		SmartPointer<IRenderTarget>	m_pDefaultRenderTarget;
		SmartPointer<RenderView>	m_pActiveView;
		RenderSystem();
		friend class RenderManager;
	};
}


