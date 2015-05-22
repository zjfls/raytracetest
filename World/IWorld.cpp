#include "stdafx.h"
#include "IWorld.h"
#include "IWorldObj.h"
#include "LightBase.h"
#include "IRenderable.h"

IWorld::IWorld()
{
	m_pRoot = shared_ptr<IWorldObj>(IWorldObj::CreateWorldObj());
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

std::vector<shared_ptr<IRenderable>> IWorld::GetAllRenderables()
{
	std::vector<shared_ptr<IRenderable>> vecRenderables;
	m_pRoot->GetRenderableRecursive(vecRenderables);
	return vecRenderables;
}

void IWorld::GetRenderablesLightInfo(std::vector<shared_ptr<IRenderable>>& vec)
{
	std::vector<shared_ptr<LightBase>> vecLight = GetAllModules<LightBase>();
	for each (shared_ptr<IRenderable> pRenderable in vec)
	{
		pRenderable->m_vecLight.clear();
		for each (shared_ptr<LightBase> pLight in vecLight)
		{
			pRenderable->m_vecLight.push_back(pLight);
		}
	}
}

