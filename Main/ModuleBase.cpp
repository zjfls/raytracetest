#include "stdafx.h"
#include "ModuleBase.h"
#include "IWorldObj.h"
#include <iostream>

ModuleBase::ModuleBase()
	:m_bTransformUpdated(false)
	, m_bActive(true)
	, m_bInitialized(false)
	, m_bStarted(false)
{
	//std::cout << "build module obj" << std::endl;
}


ModuleBase::~ModuleBase()
{
	//std::cout << "release module obj" << std::endl;
}

void ZG::ModuleBase::Added()
{
	OnAdded();
}

void ZG::ModuleBase::Removed()
{
	m_bStarted = false;
	OnRemoved();
}

void ZG::ModuleBase::Update()
{
	if (m_bActive == false)
	{
		return;
	}
	if (m_bInitialized == false)
	{
		OnInitialize();
		m_bInitialized = true;
	}
	if (m_bStarted == false)
	{
		OnStart();
		m_bStarted = true;
	}
	OnUpdate();
}

void ZG::ModuleBase::SetActive(bool bActive)
{
	if (m_bActive == false && bActive == true)
	{
		OnActive();
	}
	if (m_bActive == true && bActive == false)
	{
		OnDeactive();
	}
	m_bActive = bActive;
}

bool ZG::ModuleBase::IsActive()
{
	return m_bActive;
}
