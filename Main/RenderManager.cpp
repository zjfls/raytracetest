#include "stdafx.h"
#include "RenderManager.h"
#include "EnviromentSetting.h"
#include "RenderPathManager.h"
#include "RenderView.h"
#include "RenderPath.h"
#include "RenderSystem.h"
#ifdef WIN32
//#include "D3D9Render.h"
//#include "D3D9RenderSystem.h"
#include "windows.h"
#endif
typedef RenderSystem* (WINAPI *CreateRSMethod)();
template class MAIN_API Singleton < RenderManager >;
template<> shared_ptr<RenderManager> Singleton<RenderManager>::_instance = nullptr;

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
	string renderPath = EnviromentSetting::GetInstance()->GetSetting("RenderPath");
	RenderPath* pRenderPath = RenderPathManager::GetInstance()->GetRenderPath(renderPath);
#ifdef WIN32
	if (renderType == "D3D9")
	{
		HMODULE hRenderDLL = LoadLibrary("D3D9Render.dll");
		CreateRSMethod pFunc = (CreateRSMethod)GetProcAddress(hRenderDLL, "CreateRenderSystem");
		m_mapRenderSystem["D3D9"] = pFunc();
		//m_mapRenderSystem["D3D9"] = new D3D9RenderSystem();
		bool b = m_mapRenderSystem["D3D9"]->InitRenderSystem(renderViewInfo);
		m_mapRenderSystem["D3D9"]->CreateDefaultRender(pRenderPath);
		m_pDefualtRenderSystem = m_mapRenderSystem["D3D9"];
		return b;
	}
#endif
	return true;
}

//IRender* RenderManager::GetDefaultRender()
//{
//	return m_pDefaultRender;
//}
//
//RenderView* RenderManager::GetDefaultRenderView()
//{
//	return m_pDefaultRenderView;
//}
