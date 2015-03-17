#include "stdafx.h"
#include "SkeletonResource.h"
#include "ResourceMananger.h"
ResourceManager<SkeletonResource>* Singleton<ResourceManager<SkeletonResource>>::_instance = nullptr;

SkeletonResource::SkeletonResource()
{
}


SkeletonResource::~SkeletonResource()
{
}

int Bone::GetBoneIndexByName(string name)
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
