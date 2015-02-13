#include "stdafx.h"
#include "IWorld.h"
IWorld* IWorld::pSingleWorld = nullptr;

IWorld::IWorld()
{
	m_pRoot = new IWorldObj();
	pSingleWorld = this;
}


IWorld::~IWorld()
{
}

void IWorld::Update()
{
	m_pRoot->Update();
}

std::vector<IRenderable*> IWorld::GetAllRenderables()
{
	std::vector<IRenderable*> vecRenderables;
	m_pRoot->GetRenderableRecursive(vecRenderables);
	return vecRenderables;
}
