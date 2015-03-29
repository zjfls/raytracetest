#include "stdafx.h"
#include "IWorld.h"
#include "IWorldObj.h"


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
	}
}

std::vector<IRenderable*> IWorld::GetAllRenderables()
{
	std::vector<IRenderable*> vecRenderables;
	m_pRoot->GetRenderableRecursive(vecRenderables);
	return vecRenderables;
}

