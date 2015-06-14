#include "stdafx.h"
#include "skeleton.h"
#include "Mesh.h"
#include "IWorldObj.h"
#include "SkeletonObj.h"

SkeletonModule::SkeletonModule()
	: m_pSkeletonRoot(nullptr)
{
}


SkeletonModule::~SkeletonModule()
{
}

void SkeletonModule::AddMesh(SmartPointer<Mesh> pMesh)
{
	if (m_pOwnerObj->IsHaveModule<Mesh>(pMesh) == false)
	{
		return;
	}
	for each (SmartPointer<Mesh> var in m_MeshVec)
	{
		if (var == pMesh)
		{
			return;
		}
	}
	m_MeshVec.push_back(pMesh);
}

void SkeletonModule::GenerateSkeletonObj()
{

}

SmartPointer<ModuleBase> ZG::SkeletonModule::Clone()
{
	SkeletonModule* pCloneModule = new SkeletonModule;
	pCloneModule->m_strName = m_strName;

	pCloneModule->m_bActive = m_bActive;
	pCloneModule->m_bTransformUpdated = m_bTransformUpdated;
	pCloneModule->m_pSkeletonRoot = nullptr;
	pCloneModule->m_SkeletonRes = m_SkeletonRes;
	return pCloneModule;
}

void ZG::SkeletonModule::Update()
{
	
	if (m_pSkeletonRoot == nullptr && m_pOwnerObj != nullptr)
	{
		int nChild = m_pOwnerObj->GetChildCount();
		for (int i = 0; i < nChild; ++i)
		{
			IWorldObj* pObj = m_pOwnerObj->GetChild(i).get();
			if (dynamic_cast<SkeletonObj*>(pObj) != nullptr)
			{
				m_pSkeletonRoot = dynamic_cast<SkeletonObj*>(pObj);
			}
		}
		if (m_pSkeletonRoot == nullptr)
		{
			GenerateSkeletonArchi();
		}
	}
}

void ZG::SkeletonModule::GenerateSkeletonArchi()
{

}
