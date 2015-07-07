#include "stdafx.h"
#include "skeleton.h"
#include "Mesh.h"
#include "IWorldObj.h"
#include "SkeletonObj.h"
#include "AnimationTrack.h"
#include "SkeletonResource.h"
#include "vertexData.h"
#include "SkeletonResource.h"
#include "RasterMaterial.h"
#include "MaterialPass.h"
#include "VertexShader.h"
#include "AnimationResource.h"
#include "Transform.h"
#include "AnimationTrack.h"
#include "FragShader.h"
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
	//if (m_pOwnerObj->IsHaveModule<Mesh>(pMesh) == false)
	//{
	//	return;
	//}
	for each (SmartPointer<Mesh> var in m_MeshVec)
	{
		if (var == pMesh)
		{
			return;
		}
	}
	//pMesh->m_pVertexData->m_SkinMatrix = m_SkinMatrix;
	m_MeshVec.push_back(pMesh);
	//
	if (pMesh->m_pVertexData->m_nBoneNumber > MAX_BONE_NUMBER)
	{
		pMesh->SetCpuSkin(true);
		MaterialResource* pMat = pMesh->GetMaterialInstance().get();
		if (pMat != nullptr)
		{
			RasterMaterial* pRstMat = dynamic_cast<RasterMaterial*>(pMat);
			for each (std::pair<std::string,SmartPointer<MaterialPass>> var in pRstMat->m_MaterialPass)
			{
				var.second->m_pVertexShader =  ResourceManager<VertexShader>::GetInstance()->GetResource("./data/shader/VertexStandard.vsm");
			}
		}

	}
	else
	{
		pMesh->m_pSkinMatrixInfo = m_SkinMatrix;
	}
	//
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
	for each (SmartPointer<AnimationTrack> pTrack in m_vecTracks)
	{
		AnimationTrack* pAniTrack = new AnimationTrack(pTrack->m_pResource.get());
		pCloneModule->m_vecTracks.push_back(pAniTrack);
		if (pTrack == m_pDefaultTrack)
		{
			pCloneModule->SetDefaultAnimationTrack(pAniTrack);
		}
	}


	return pCloneModule;
}

void ZG::SkeletonModule::OnUpdate()
{
	AnimationModule::OnUpdate();
	if (m_vecActiveTrack.size() != 0.0f)
	{
		m_pOwnerObj->m_pTransform->m_bDirt = true;
	}

}

void ZG::SkeletonModule::GenerateSkeletonArchi()
{

}

bool ZG::SkeletonModule::BindAnimation(AnimationTrack* pTrack)
{
	if (m_bInitialized == false)
	{
		return false;
	}
	if (pTrack->GetBind() == true)
	{
		pTrack->ClearBind();
	}
	pTrack->SetBind(true);
	//for (int i = 0; i < pTrack->m_pResource->m_mapCurves.size();++i)
	for each (std::pair<std::string, SmartPointer<AnimationCurveBase>> p in pTrack->m_pResource->m_mapCurves)
	{
		if (m_mapNameToSkeletonObj.find(p.first) != std::end(m_mapNameToSkeletonObj))
		{
			pTrack->AddBind<stTransformData>(p.first, &(m_mapNameToSkeletonObj[p.first]->m_pTransform->m_TransformData));
		}
	}
	return true;
}

void ZG::SkeletonModule::OnInitialize()
{
	if (m_pOwnerObj == nullptr || m_SkeletonRes == nullptr)
	{
		return;
	}
	int nChild = m_pOwnerObj->GetChildCount();
	std::vector < SmartPointer<Mesh>> vecMesh;
	m_pOwnerObj->GetAllModuleRecursive<Mesh>(vecMesh);
	//
	for each (SmartPointer<Mesh> pMesh in vecMesh)
	{
		if (pMesh->m_pVertexData->m_nBoneNumber > 0)
		{
			AddMesh(pMesh);
		}
	}
	//
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
			//std::cout << "Find Bone" << i << ":" << pBone->m_strName.c_str() << std::endl;;
		}
		m_mapSkeletonObj[i] = pObj;
		m_mapNameToSkeletonObj[pBone->m_strName] = pObj;

	}
}
void ZG::SkeletonModule::OnLateUpdate()
{

	for (int i = 0; i < m_mapSkeletonObj.size(); ++i)
	{
		m_SkinMatrix->matArray[i] = m_SkeletonRes->m_mapBone[i]->m_matInversePos * m_mapSkeletonObj[i]->m_pTransform->GetWorldMatrix();
		//m_SkinMatrix->matArray[i] = m_pOwnerObj->m_pTransform->GetWorldMatrix();
		//Matrix44 mat = m_pOwnerObj->m_pTransform->GetWorldMatrix();
		//Matrix44 mat2 = m_SkinMatrix->matArray[i];
		int c = 0;
	}
}

void ZG::SkeletonModule::SetSkeletonRes(SkeletonResource* pRes)
{
	m_SkeletonRes = pRes;
	m_SkinMatrix->nSize = pRes->m_nBoneNum;
}

bool ZG::SkeletonModule::PlayAnimation(AnimationTrack* pTrack)
{
	if (m_vecActiveTrack.size() > 0 && pTrack == m_vecActiveTrack[0])
	{
		return true;
	}
	if (pTrack->GetBind() == true)
	{

	}
	else
	{
		BindAnimation(pTrack);
	}
	//
	m_vecActiveTrack.clear();
	m_vecActiveTrack.push_back(pTrack);
	pTrack->Start();
	return true;
}

void ZG::SkeletonModule::OnStart()
{
	AnimationModule::OnStart();
}

SkeletonResource* ZG::SkeletonModule::GetSkeletonRes()
{
	return m_SkeletonRes.get();
}
