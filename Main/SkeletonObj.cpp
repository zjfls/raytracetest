#include "stdafx.h"
#include "SkeletonObj.h"


SkeletonObj::SkeletonObj()
	:m_bIsRoot(false)
{
}


SkeletonObj::~SkeletonObj()
{
}

void SkeletonObj::OnAdded()
{
	//Todo:generate node
}

SmartPointer<IWorldObj> ZG::SkeletonObj::Clone(bool bRecursive)
{
	SkeletonObj* pCloneObj = new SkeletonObj;
	pCloneObj->m_bIsRoot = m_bIsRoot;
	pCloneObj->m_strName = m_strName;
	pCloneObj->removeModule(pCloneObj->m_pTransform.SmartPointerCast<ModuleBase>());
	for each (SmartPointer<ModuleBase> pModule in m_vecModules)
	{
		SmartPointer<ModuleBase> pCloneModule = pModule->Clone();
		pCloneModule->m_pOwnerObj = pCloneObj;
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
