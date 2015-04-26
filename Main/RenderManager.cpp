#include "stdafx.h"
#include "RenderManager.h"
#include "EnviromentSetting.h"
#include "RenderPathManager.h"
#include "RenderView.h"
#include "RenderPath.h"
#include "RenderSystem.h"
#include "AssetManager.h"
#include "ResourceManager.h"
#include "FragShader.h"
#ifdef WIN32
//#include "D3D9Render.h"
//#include "D3D9RenderSystem.h"
#include "windows.h"
#include "ShaderGenerator.h"
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
		//return b;
	}
#endif
	//Create Default RenderTarget Group
	bool bHdr = EnviromentSetting::GetInstance()->GetIntSetting("HDR");
	if (bHdr == true)
	{
		IRenderTarget* pRenderTarget = m_pDefualtRenderSystem->CreateRenderTarget(renderViewInfo.m_nWidth, renderViewInfo.m_nHeight, TFA16B16G16R16F, MSNONE, 0);
		if (pRenderTarget == nullptr)
		{
			m_pDefualtRenderSystem->m_pDefaultRenderTarget = m_pDefualtRenderSystem->m_pDefaultRenderView;
		}
		else
		{
			m_pDefualtRenderSystem->m_pDefaultRenderTarget = pRenderTarget;
		}
	}
	else
	{
		m_pDefualtRenderSystem->m_pDefaultRenderTarget = m_pDefualtRenderSystem->m_pDefaultRenderView;
	}
	pRenderPath->InitTargetBuffer();

	LoadShaderChunk();
	return true;
}

bool RenderManager::LoadShaderChunk()
{
	AssetManager::GetInstance()->LoadAsset("./data/shader/common/lightatten.srf");
	AssetManager::GetInstance()->LoadAsset("./data/shader/common/surfaceblinnphong.srf");
	AssetManager::GetInstance()->LoadAsset("./data/shader/common/debug.srf");
	ShaderGenerator::m_mapCode["lightatten"] = ResourceManager<FragShader>::GetInstance()->GetResource("./data/shader/common/lightatten.srf")->m_pCodeBuffer;
	ShaderGenerator::m_mapCode["surfaceblinnphong"] = ResourceManager<FragShader>::GetInstance()->GetResource("./data/shader/common/surfaceblinnphong.srf")->m_pCodeBuffer;
	ShaderGenerator::m_mapCode["debug"] = ResourceManager<FragShader>::GetInstance()->GetResource("./data/shader/common/debug.srf")->m_pCodeBuffer;
	//
	ShaderGenerator::m_vecPPParam.push_back("VIEW_POS");

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
