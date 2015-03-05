#include "stdafx.h"
#include "ApplicationBase.h"
#include "Transform.h"
#include "Sphere3D.h"
#include "RayTraceCamera.h"
#include "IWorld.h"
#include "AssetManager.h"
#include "FbxFileLoader.h"

ApplicationBase::ApplicationBase()
{
}


ApplicationBase::~ApplicationBase()
{
}

bool ApplicationBase::Init()
{
	AssetManager::GetInstance()->Init();
	OnInit();
	OnSetupScene();
	if (m_pWorld != nullptr)
	{
		m_pWorld->Update();
	}
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

void ApplicationBase::OnSetupScene()
{

}


