#include "stdafx.h"
#include "ApplicationBase.h"
#include "Transform.h"
#include "Sphere3D.h"
#include "RayTraceCamera.h"
#include "IWorld.h"
#include "AssetManager.h"
#include "FbxAppManager.h"
#include "RenderManager.h"
#include "EnviromentSetting.h"
#include "RenderPathManager.h"
#include "RenderView.h"
#include <direct.h>
#include "RenderSystem.h"
#include "BuiltInResource.h"
ApplicationBase::ApplicationBase()
	:m_pRenderView(nullptr)
{
}


ApplicationBase::~ApplicationBase()
{
}

bool ApplicationBase::Init(int argc, char** argv)
{
	
	_chdir("../");
	m_argc = argc;
	m_argv = argv;
	if (false == EnviromentSetting::GetInstance()->Init())
	{
		return false;
	}
	ReadSettings();
	CreateAppWindow();
	if (false == RenderPathManager::GetInstance()->Init())
	{
		return false;
	}
	if (false == FbxAppManager::GetInstance()->Init())
	{
		return false;
	}
	if (false == AssetManager::GetInstance()->Init())
	{
		return false;
	}
	if (false == RenderManager::GetInstance()->Init(m_RenderViewInfo))
	{
		return false;
	}
	if (false == BuiltInResource::GetInstance()->InitBuiltInResource())
	{
		return false;
	}
	m_pRenderView = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();



	m_pWorld = new IWorld;
	OnInit();
	SetupScene();
	if (m_pWorld != nullptr)
	{
		m_pWorld->Update();
	}
	OnEndInit();
	return true;
}

void ApplicationBase::OnEndInit()
{

}

void ApplicationBase::PreUpdate()
{

}

void ApplicationBase::OnUpdate()
{

}

void ApplicationBase::OnInit()
{

}

void ApplicationBase::SetupScene()
{

}

void ApplicationBase::Run()
{

}

bool ApplicationBase::CreateAppWindow()
{
	return true;
}

void ApplicationBase::ReadSettings()
{
	int width = EnviromentSetting::GetInstance()->GetIntSetting("Width");
	int height = EnviromentSetting::GetInstance()->GetIntSetting("Height");
	//m_RenderViewInfo.m_windowID = (unsigned int)window;
	m_RenderViewInfo.m_nHeight = width;
	m_RenderViewInfo.m_nWidth = height;
	m_RenderViewInfo.m_bWindowed = (bool)EnviromentSetting::GetInstance()->GetIntSetting("Windowed");
}


