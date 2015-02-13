#include "stdafx.h"
#include "ApplicationBase.h"
#include "Transform.h"
#include "Sphere3D.h"
#include "RayTraceCamera.h"
#include "IWorld.h"

ApplicationBase::ApplicationBase()
{
}


ApplicationBase::~ApplicationBase()
{
}

bool ApplicationBase::Init()
{
	OnInit();
	OnSetupScene();
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

void ApplicationBase::OnSetupScene()
{

}


