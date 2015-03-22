#pragma once
class IRender;
class RenderView;
class RenderSystem;
struct stRenderViewInfo;
class RenderManager :public Singleton < RenderManager >
{
public:
	RenderManager();
	virtual ~RenderManager();
	bool	 Init(const stRenderViewInfo& renderViewInfo);


	//IRender* CreateRenderBySetting(void* pArg);
	//IRender* CreateRender(string strType,void* pArg);


	IRender* GetDefaultRender();
	RenderView* GetDefaultRenderView();
private:


private:
	IRender*	m_pDefaultRender;
	RenderView*	m_pDefaultRenderView;
	RenderSystem* m_pRenderSystem;
};

