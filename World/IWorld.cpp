#include "stdafx.h"
#include "IWorld.h"
#include "IWorldObj.h"
#include "LightBase.h"
#include "IRenderable.h"
#include "MaterialResource.h"

IWorld::IWorld()
{
	m_pRoot = SmartPointer<IWorldObj>(IWorldObj::CreateWorldObj());
	m_pRoot->m_strName = "SceneRoot";
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

std::vector<SmartPointer<IRenderable>> IWorld::GetAllRenderables()
{
	std::vector<SmartPointer<IRenderable>> vecRenderables;
	m_pRoot->GetRenderableRecursive(vecRenderables);
	return vecRenderables;
}

void IWorld::GetRenderablesLightInfo(std::vector<SmartPointer<IRenderable>>& vec)
{
	std::vector<SmartPointer<LightBase>> vecLight = GetAllModules<LightBase>();
	for each (SmartPointer<IRenderable> pRenderable in vec)
	{
		pRenderable->m_vecLight.clear();
		for each (SmartPointer<LightBase> pLight in vecLight)
		{
			pRenderable->m_vecLight.push_back(pLight);
		}
	}
}

