#include "stdafx.h"
#include "IWorld.h"
#include "IWorldObj.h"
#include "LightBase.h"
#include "IRenderable.h"

IWorld::IWorld()
{
	m_pRoot = new IWorldObj();
}


IWorld::~IWorld()
{
}

void IWorld::Update()
{
	if (m_pRoot != nullptr)
	{
		m_pRoot->Update();
		m_pRoot->AfterUpdate();
	}
}

std::vector<IRenderable*> IWorld::GetAllRenderables()
{
	std::vector<IRenderable*> vecRenderables;
	m_pRoot->GetRenderableRecursive(vecRenderables);
	return vecRenderables;
}

void IWorld::GetRenderablesLightInfo(std::vector<IRenderable*>& vec)
{
	std::vector<LightBase*> vecLight = GetAllModules<LightBase>();
	for each (IRenderable* pRenderable in vec)
	{
		pRenderable->m_vecLight.clear();
		for each (LightBase* pLight in vecLight)
		{
			pRenderable->m_vecLight.push_back(pLight);
		}
	}
}

