#pragma once
#include "IResource.h"
#include "ResourceMananger.h"
class Bone
{
public:
	Vector3 t;
	Vector3 r;
	Vector3 s;
	string m_strName;
	unsigned int		nIndex;
	std::vector<Bone*> vecChild;
	int GetBoneIndexByName(string name);
};
class SkeletonResource :
	public IResource
{
public:
	SkeletonResource();
	~SkeletonResource();

	
	Bone* m_pRoot;
	friend class ResourceManager<SkeletonResource>;
	std::map<int, Bone*> m_mapBone;//index to bone;
	unsigned int m_nBoneNum;
};

