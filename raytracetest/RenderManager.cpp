#include "stdafx.h"
#include "RenderManager.h"
#include "EnviromentSetting.h"
#include "RenderPathManager.h"
#include "RenderView.h"
#include "RenderPath.h"
#ifdef WIN32
#include "D3D9Render.h"
#include "D3D9RenderSystem.h"
#endif
RenderManager* Singleton<RenderManager>::_instance = nullptr;

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}


bool RenderManager::Init(const stRenderViewInfo& renderViewInfo)
{
	//stRenderViewInfo renderViewInfo;
	string renderType = EnviromentSetting::GetInstance()->GetSetting("RenderType");
	RenderPath* pRenderPath = RenderPathManager::GetInstance()->GetRenderPath(EnviromentSetting::GetInstance()->GetSetting("RenderPath"));
#ifdef WIN32
	if (renderType == "D3D9")
	{
		m_pRenderSystem = new D3D9RenderSystem();
		bool b = m_pRenderSystem->InitRenderSystem(renderViewInfo);
		m_pRenderSystem->CreateDefaultRender(pRenderPath);
		return b;
	}
#endif
	return true;
}

IRender* RenderManager::GetDefaultRender()
{
	return m_pDefaultRender;
}

RenderView* RenderManager::GetDefaultRenderView()
{
	return m_pDefaultRenderView;
}
