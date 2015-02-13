#include "stdafx.h"
#include "IWorldObj.h"


IWorldObj::IWorldObj()
{
	//m_pTransform = new Transform;
	m_pTransform = (Transform*)addModule<Transform>();
}


IWorldObj::~IWorldObj()
{
	for each (ModuleBase* var in m_vecModules)
	{
		delete var;
	}
	for each (IWorldObj* var in m_vecChildren)
	{
		delete var;
	}
}

bool IWorldObj::addChild(IWorldObj* pObj)
{
	assert(pObj->m_pParent == nullptr);
	for each (IWorldObj* var in m_vecChildren)
	{
		if (var == pObj)
		{ 
			return false;
		}
	}
	pObj->m_pParent = this;
	m_vecChildren.push_back(pObj);
	return true;
}

bool IWorldObj::removeChild(IWorldObj* pObj)
{
	std::vector<IWorldObj*>::iterator iter;
	for (iter == m_vecChildren.begin(); iter != m_vecChildren.end(); ++iter)
	{
		if (*iter == pObj)
		{
			pObj->m_pParent = nullptr;
			m_vecChildren.erase(iter);
			return true;
		}
	}
	return false;
}

bool IWorldObj::removeModule(ModuleBase* pModule)
{
	std::vector<ModuleBase*>::iterator iter = m_vecModules.begin();
	for (; iter != m_vecModules.end(); ++iter)
	{
		if (*iter == pModule)
		{
			pModule->m_pOwnerObj = nullptr;
			m_vecModules.erase(iter);
			return true;
		}
	}
	return false;
}

void IWorldObj::Update()
{
	for each (ModuleBase* var in m_vecModules)
	{
		var->Update();
	}
	for each (IWorldObj* varChild in m_vecChildren)
	{
		varChild->Update();
	}
}

void IWorldObj::GetRenderableRecursive(std::vector<IRenderable*>& vecRenderabls)
{
	for each (ModuleBase*  var in m_vecModules)
	{
		IRenderable* pRenderable = dynamic_cast<IRenderable*>(var);
		if (pRenderable != nullptr)
		{
			vecRenderabls.push_back(pRenderable);
		}
	}
	for each (IWorldObj* var in m_vecChildren)
	{
		var->GetRenderableRecursive(vecRenderabls);
	}
}
