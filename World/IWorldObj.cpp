#include "stdafx.h"
#include "IWorldObj.h"
#include "ModuleBase.h"

IWorldObj::IWorldObj()
	:m_pParent(nullptr)
{
	
	//m_pTransform = addModule<Transform>(nullptr);
}


IWorldObj::~IWorldObj()
{

}

bool IWorldObj::addChild(shared_ptr<IWorldObj> pObj)
{
	assert(pObj->m_pParent == nullptr);
	for each (shared_ptr<IWorldObj> var in m_vecChildren)
	{
		if (var == pObj)
		{ 
			return false;
		}
	}
	pObj->m_pParent = this;// shared_ptr<IWorldObj>(this);
	m_vecChildren.push_back(pObj);
	return true;
}

bool IWorldObj::removeChild(shared_ptr<IWorldObj> pObj)
{
	std::vector<shared_ptr<IWorldObj>>::iterator iter;
	for (iter = m_vecChildren.begin(); iter != m_vecChildren.end(); ++iter)
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

bool IWorldObj::removeModule(shared_ptr<ModuleBase> pModule)
{
	std::vector<shared_ptr<ModuleBase>>::iterator iter = m_vecModules.begin();
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

void IWorldObj::Update()
{
	for each (shared_ptr<ModuleBase> var in m_vecModules)
	{
		var->Update(var);
	}
	for each (shared_ptr<IWorldObj> varChild in m_vecChildren)
	{
		varChild->Update();
	}
}

void IWorldObj::GetRenderableRecursive(std::vector<shared_ptr<IRenderable>>& vecRenderabls)
{
	for each (shared_ptr<ModuleBase>  var in m_vecModules)
	{
		shared_ptr<IRenderable> pRenderable = dynamic_pointer_cast<IRenderable>(var);
		if (pRenderable != nullptr)
		{
			vecRenderabls.push_back(pRenderable);
		}
	}
	for each (shared_ptr<IWorldObj> var in m_vecChildren)
	{
		var->GetRenderableRecursive(vecRenderabls);
	}
}

unsigned int IWorldObj::GetModuleCount() const
{
	return m_vecModules.size();
}

shared_ptr<ModuleBase> IWorldObj::GetModule(int i) const
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

shared_ptr<IWorldObj> IWorldObj::GetChild(unsigned int i) const
{
	if (i > m_vecChildren.size() || i < 0)
	{
		return nullptr;
	}
	return m_vecChildren[i];
}

shared_ptr<IWorldObj> IWorldObj::Clone(bool bRecursive)
{
	shared_ptr<IWorldObj> pCloneObj = shared_ptr<IWorldObj>(IWorldObj::CreateWorldObj());
	pCloneObj->m_strName = m_strName;
	pCloneObj->removeModule(pCloneObj->m_pTransform);
	for each (shared_ptr<ModuleBase> pModule in m_vecModules)
	{
		shared_ptr<ModuleBase> pCloneModule = pModule->Clone();
		pCloneModule->m_pOwnerObj = pCloneObj;
		pCloneObj->m_vecModules.push_back(pCloneModule);

		shared_ptr<Transform> pTrans = dynamic_pointer_cast<Transform>(pCloneModule);
		if (pTrans != nullptr)
		{
			pCloneObj->m_pTransform = pTrans;
		}
	}

	if (bRecursive)
	{
		for each (shared_ptr<IWorldObj> pChild in m_vecChildren)
		{
			shared_ptr<IWorldObj> pCloneChild = pChild->Clone(bRecursive);
			pCloneObj->addChild(pCloneChild);
		}
	}


	return pCloneObj;
}

void IWorldObj::AfterUpdate()
{
	for each (shared_ptr<ModuleBase> pModule in m_vecModules)
	{
		pModule->OnLateUpdate(pModule);
	}
	for each (shared_ptr<IWorldObj> pObj in m_vecChildren)
	{
		pObj->AfterUpdate();
	}
}
