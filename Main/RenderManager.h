#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <string>
namespace ZG
{
	class IRender;
	class RenderView;
	class RenderSystem;
	struct stRenderViewInfo;
	class MAIN_API RenderManager :public Singleton < RenderManager >, public GameObjectBase
	{
	public:
		RenderManager();
		virtual ~RenderManager();
		bool	 Init(stRenderViewInfo& renderViewInfo);


		//IRender* CreateRenderBySetting(void* pArg);
		//IRender* CreateRender(string strType,void* pArg);


		//IRender* GetDefaultRender();
		//RenderView* GetDefaultRenderView();
		RenderSystem*	GetDefaultRenderSystem() const{ return m_pDefualtRenderSystem; };
	private:
		bool LoadShaderChunk();

	private:
		//IRender*	m_pDefaultRender;
		//RenderView*	m_pDefaultRenderView;
		RenderSystem* m_pDefualtRenderSystem;

		std::unordered_map<std::string, RenderSystem*> m_mapRenderSystem;
	};
}

extern template class MAIN_API Singleton < RenderManager > ;