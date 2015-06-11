#include "stdafx.h"
#include "ModuleBase.h"
#include "IWorldObj.h"

ModuleBase::ModuleBase()
	:m_bTransformUpdated(false)
	, m_bActive(true)
{
}


ModuleBase::~ModuleBase()
{
}

void ModuleBase::OnLateUpdate()
{

}

void ModuleBase::Update()
{

}
