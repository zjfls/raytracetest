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
