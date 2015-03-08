#include "stdafx.h"
#include "ApplicationBase.h"
#include "Transform.h"
#include "Sphere3D.h"
#include "RayTraceCamera.h"
#include "IWorld.h"
#include "AssetManager.h"
#include "FbxAppManager.h"

ApplicationBase::ApplicationBase()
{
}


ApplicationBase::~ApplicationBase()
{
}

bool ApplicationBase::Init(int argc, char** argv)
{
	m_argc = argc;
	m_argv = argv;
	FbxAppManager::GetInstance()->Init();
	AssetManager::GetInstance()->Init();
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


