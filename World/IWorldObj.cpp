#include "stdafx.h"
#include "IWorldObj.h"
#include "ModuleBase.h"

IWorldObj::IWorldObj()
	:m_pParent(nullptr)
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

unsigned int IWorldObj::GetModuleCount() const
{
	return m_vecModules.size();
}

ModuleBase* IWorldObj::GetModule(int i) const
{
	if (i >= m_vecModules.size() || i < 0)
	{
		return nullptr;
	}
	return m_vecModules[i];
}

unsigned int IWorldObj::GetChildCount() const
{
	return m_vecChildren.size();
}

IWorldObj* IWorldObj::GetChild(int i) const
{
	if (i > m_vecChildren.size() || i < 0)
	{
		return nullptr;
	}
	return m_vecChildren[i];
}

IWorldObj* IWorldObj::Clone(bool bRecursive)
{
	IWorldObj* pCloneObj = new IWorldObj;
	pCloneObj->m_strName = m_strName;
	//pCloneObj->m_pParent = m_pParent;
	pCloneObj->removeModule(pCloneObj->m_pTransform);
	for each (ModuleBase* pModule in m_vecModules)
	{
		ModuleBase* pCloneModule = pModule->Clone();
		pCloneModule->m_pOwnerObj = pCloneObj;
		pCloneObj->m_vecModules.push_back(pCloneModule);
	}

	if (bRecursive)
	{
		for each (IWorldObj* pChild in m_vecChildren)
		{
			IWorldObj* pCloneChild = pChild->Clone(bRecursive);
			pCloneObj->addChild(pCloneChild);
		}
	}


	return pCloneObj;
}
