#include "stdafx.h"
#include "SkeletonResource.h"
#include "ResourceManager.h"
#include "Matrix33.h"
SmartPointer<ResourceManager<SkeletonResource>> Singleton<ResourceManager<SkeletonResource>>::_instance = nullptr;

SkeletonResource::SkeletonResource()
{
}


SkeletonResource::~SkeletonResource()
{
}

void ZG::SkeletonResource::UpdateMatrix()
{
	m_pRoot->UpdateMatrix(Matrix44::Identity);
}

int Bone::GetBoneIndexByName(std::string name)
{
	if (name == m_strName)
	{
		return nIndex;
	}
	for each (Bone* pChild in vecChild)
	{
		int rt = pChild->GetBoneIndexByName(name);
		if (rt >= 0)
		{
			return rt;
		}
	}
	return -1;
}

void ZG::Bone::UpdateMatrix(Matrix44 parentMat)
{

}
