#include "stdafx.h"
#include "IWorldObj.h"
#include "ModuleBase.h"
#include "IRenderable.h"
#include "MaterialResource.h"
#include "CameraBase.h"
#include "IWorld.h"
#include "AABBBox.h"
IWorldObj::IWorldObj()
	:m_pParent(nullptr)
{
	m_strName = "WorldObj";
	m_pTransform = addModule<Transform>();
	//std::cout << "build world obj" << std::endl;
}


IWorldObj::~IWorldObj()
{
	//std::cout << "release world obj" << std::endl;
}

bool IWorldObj::addChild(SmartPointer<IWorldObj> pObj)
{
	assert(pObj->m_pParent == nullptr);
	for each (SmartPointer<IWorldObj> var in m_vecChildren)
	{
		if (var == pObj)
		{ 
			return false;
		}
	}
	pObj->m_pParent = this;// SmartPointer<IWorldObj>(this);
	m_vecChildren.push_back(pObj);

	pObj->OnAdd();
	return true;
}

bool IWorldObj::removeChild(SmartPointer<IWorldObj> pObj)
{
	std::vector<SmartPointer<IWorldObj>>::iterator iter;
	for (iter = m_vecChildren.begin(); iter != m_vecChildren.end(); ++iter)
	{
		if (*iter == pObj)
		{
			pObj->m_pParent = nullptr;
			m_vecChildren.erase(iter);
			return true;
		}
	}

	pObj->OnRemove();
	return false;
}

bool IWorldObj::removeModule(SmartPointer<ModuleBase> pModule)
{
	std::vector<SmartPointer<ModuleBase>>::iterator iter = m_vecModules.begin();
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
	for each (SmartPointer<ModuleBase> var in m_vecModules)
	{
		var->Update();
	}
	for each (SmartPointer<IWorldObj> varChild in m_vecChildren)
	{
		varChild->Update();
	}
}

void IWorldObj::GetRenderableRecursive(std::vector<SmartPointer<IRenderable>>& vecRenderabls)
{
	for each (SmartPointer<ModuleBase>  var in m_vecModules)
	{
		SmartPointer<IRenderable> pRenderable = var.SmartPointerCast<IRenderable>();
		if (pRenderable != nullptr)
		{
			vecRenderabls.push_back(pRenderable);
		}
	}
	for each (SmartPointer<IWorldObj> var in m_vecChildren)
	{
		var->GetRenderableRecursive(vecRenderabls);
	}
}

unsigned int IWorldObj::GetModuleCount() const
{
	return m_vecModules.size();
}

SmartPointer<ModuleBase> IWorldObj::GetModule(int i) const
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

SmartPointer<IWorldObj> IWorldObj::GetChild(unsigned int i) const
{
	if (i > m_vecChildren.size() || i < 0)
	{
		return nullptr;
	}
	return m_vecChildren[i];
}

SmartPointer<IWorldObj> IWorldObj::Clone(bool bRecursive)
{
	SmartPointer<IWorldObj> pCloneObj = SmartPointer<IWorldObj>(new IWorldObj);
	pCloneObj->m_strName = m_strName;
	pCloneObj->removeModule(pCloneObj->m_pTransform.SmartPointerCast<ModuleBase>());
	for each (SmartPointer<ModuleBase> pModule in m_vecModules)
	{
		SmartPointer<ModuleBase> pCloneModule = pModule->Clone();
		pCloneModule->m_pOwnerObj = pCloneObj.get();
		pCloneObj->m_vecModules.push_back(pCloneModule);

		SmartPointer<Transform> pTrans = pCloneModule.SmartPointerCast<Transform>();
		if (pTrans != nullptr)
		{
			pCloneObj->m_pTransform = pTrans;
		}
	}

	if (bRecursive)
	{
		for each (SmartPointer<IWorldObj> pChild in m_vecChildren)
		{
			SmartPointer<IWorldObj> pCloneChild = pChild->Clone(bRecursive);
			pCloneObj->addChild(pCloneChild);
		}
	}


	return pCloneObj;
}

void IWorldObj::AfterUpdate()
{
	for each (SmartPointer<ModuleBase> pModule in m_vecModules)
	{
		pModule->OnLateUpdate();
	}
	for each (SmartPointer<IWorldObj> pObj in m_vecChildren)
	{
		pObj->AfterUpdate();
	}
}

bool ZG::IWorldObj::removeAllChildren()
{
	std::vector<SmartPointer<IWorldObj>>::iterator iter;
	for (iter = m_vecChildren.begin(); iter != m_vecChildren.end(); ++iter)
	{
			(*iter)->m_pParent = nullptr;
			//m_vecChildren.erase(iter);
	}
	m_vecChildren.clear();
	return true;
}

void ZG::IWorldObj::OnAdd()
{
	for each (SmartPointer<ModuleBase> pModule in m_vecModules)
	{
		pModule->Added();
	}
	for each (SmartPointer<IWorldObj> pObj in m_vecChildren)
	{
		pObj->OnAdd();
	}
}

void ZG::IWorldObj::OnRemove()
{
	for each (SmartPointer<ModuleBase> pModule in m_vecModules)
	{
		pModule->Removed();
	}
	for each (SmartPointer<IWorldObj> pObj in m_vecChildren)
	{
		pObj->OnRemove();
	}
}

IWorldObj* ZG::IWorldObj::GetChildByName(std::string strName,bool bRecursive /*= false*/)
{
	unsigned int nChildCount = m_vecChildren.size();
	for (int i = 0; i < nChildCount; ++i)
	{
		IWorldObj* pChild = m_vecChildren[i].get();
		if (pChild->m_strName == strName)
		{
			return pChild;

		}
		if (bRecursive == true)
		{
			IWorldObj* pSubChild = pChild->GetChildByName(strName, true);
			if (pSubChild != nullptr)
			{
				return pSubChild;
			}
		}
	}
	return nullptr;
}

AABBBox ZG::IWorldObj::GetWorldAABBBox()
{
	std::vector<SmartPointer<IRenderable>> vecRend;
	GetAllModule<IRenderable>(vecRend);
	AABBBox pBox;
	pBox.m_Min = m_pTransform->GetWorldTranslate() - Vector3(50.0f, 50.0f, 50.0f);
	pBox.m_Max = m_pTransform->GetWorldTranslate() + Vector3(50.0f, 50.0f, 50.0f);
	bool bInit = false;
	for each (SmartPointer<IRenderable> pRend in vecRend)
	{
		AABBBox* rendAABB = dynamic_cast<AABBBox*>(pRend->m_pBounding);
		if (bInit == false)
		{
			pBox = *rendAABB;
			bInit = true;
		}
		else
		{
			if (rendAABB != nullptr)
			{
				pBox.CombineAABB(rendAABB);
			}
		}
	}
	return pBox;
}
