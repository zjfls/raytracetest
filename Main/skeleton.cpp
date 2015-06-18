#include "stdafx.h"
#include "skeleton.h"
#include "Mesh.h"
#include "IWorldObj.h"
#include "SkeletonObj.h"
#include "AnimationTrack.h"
#include "SkeletonResource.h"
#include "vertexData.h"

SkeletonModule::SkeletonModule()
	: m_pSkeletonRoot(nullptr)
{
	m_SkinMatrix = new SkinMatrixInfo();
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
	pMesh->m_pVertexData->m_SkinMatrix = m_SkinMatrix;
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

void ZG::SkeletonModule::OnUpdate()
{


}

void ZG::SkeletonModule::GenerateSkeletonArchi()
{

}

bool ZG::SkeletonModule::BindAnimation(AnimationTrack* pTrack)
{
	pTrack->SetBind(true);
	return true;
}

void ZG::SkeletonModule::OnInitialize()
{
	if (m_pOwnerObj == nullptr || m_SkeletonRes == nullptr)
	{
		return;
	}
	int nChild = m_pOwnerObj->GetChildCount();
	for (int i = 0; i < nChild; ++i)
	{
		IWorldObj* pObj = m_pOwnerObj->GetChild(i).get();
		if (dynamic_cast<SkeletonObj*>(pObj) != nullptr)
		{
			m_pSkeletonRoot = dynamic_cast<SkeletonObj*>(pObj);
			break;
		}
	}
	if (m_pSkeletonRoot == nullptr)
	{
		GenerateSkeletonArchi();
	}
	//
	GenerateSkeletonIndexMap();
}

void ZG::SkeletonModule::GenerateSkeletonIndexMap()
{
	for (int i = 0; i < m_SkeletonRes->m_nBoneNum; ++i)
	{
		Bone* pBone = m_SkeletonRes->m_mapBone[i];
		SkeletonObj* pObj = (SkeletonObj*)m_pOwnerObj->GetChildByName(pBone->m_strName,true);
		if (pObj != nullptr)
		{
			std::cout << "Find Bone" << i << ":" << pBone->m_strName.c_str() << std::endl;;
		}
		m_mapSkeletonObj[i] = pObj;

	}
}
void ZG::SkeletonModule::OnLateUpdate()
{
	for (int i = 0; i < m_mapSkeletonObj.size(); ++i)
	{
		//m_SkinMatrix->matArray[i] = m_mapSkeletonObj[i]->m_pTransform->GetWorldMatrix();
	}
}

void ZG::SkeletonModule::SetSkeletonRes(SkeletonResource* pRes)
{
	m_SkeletonRes = pRes;
	m_SkinMatrix->nSize = pRes->m_nBoneNum;
}
