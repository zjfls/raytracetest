#include "stdafx.h"
#include "IWorldObj.h"


IWorldObj::IWorldObj()
{
	m_pTransform = new Transform;
	addModule(m_pTransform);
}


IWorldObj::~IWorldObj()
{
}

bool IWorldObj::addChild(IWorldObj* pObj)
{
	for each (IWorldObj* var in m_vecChildren)
	{
		if (var == pObj)
		{ 
			return false;
		}
	}
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
			m_vecChildren.erase(iter);
			return true;
		}
	}
	return false;
}

bool IWorldObj::addModule(ModuleBase* pModule)
{
	for each (ModuleBase* var in m_vecModules)
	{
		if (var == pModule)
		{
			return false;
		}
	}
	m_vecModules.push_back(pModule);
	return true;
}

bool IWorldObj::removeModule(ModuleBase* pModule)
{
	std::vector<ModuleBase*>::iterator iter = m_vecModules.begin();
	for (; iter != m_vecModules.end(); ++iter)
	{
		if (*iter == pModule)
		{
			m_vecModules.erase(iter);
			return true;
		}
	}
	return false;
}
