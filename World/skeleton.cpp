#include "stdafx.h"
#include "skeleton.h"
#include "Mesh.h"
#include "IWorldObj.h"

SkeletonModule::SkeletonModule()
	:m_pSkeRes(nullptr)
{
}


SkeletonModule::~SkeletonModule()
{
}

void SkeletonModule::AddMesh(shared_ptr<Mesh> pMesh)
{
	if (m_pOwnerObj->IsHaveModule<Mesh>(pMesh) == false)
	{
		return;
	}
	for each (shared_ptr<Mesh> var in m_MeshVec)
	{
		if (var == pMesh)
		{
			return;
		}
	}
	m_MeshVec.push_back(pMesh);
}

//void SkeletonModule::SetSkeletonResource(shared_ptr<SkeletonResource> pRes, bool bGenerateObj)
//{
//	m_pSkeRes = pRes;
//	if (bGenerateObj == true)
//	{
//		GenerateSkeletonObj();
//	}
//
//}

void SkeletonModule::GenerateSkeletonObj()
{

}
