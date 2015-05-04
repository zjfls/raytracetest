#pragma once
#include "ModuleBase.h"
class SkeletonObj;
class Mesh;
class SkeletonResource;
class WORLD_API SkeletonModule :public ModuleBase
{
public:
	SkeletonModule();
	virtual ~SkeletonModule();
	void	AddMesh(shared_ptr<Mesh> pMesh);


	//void	SetSkeletonResource(shared_ptr<SkeletonResource> pRes,bool bGenerateObj = true);
private:
	void	GenerateSkeletonObj();
private:
	SkeletonObj* m_pSkeletonRoot;
	std::vector<shared_ptr<Mesh>> m_MeshVec;
	shared_ptr<SkeletonResource> m_pSkeRes;
	string m_strSkeleton;
};

