#pragma once
#include "ModuleBase.h"
class SkeletonObj;
class Mesh;
class SkeletonResource;
class SkeletonModule:public ModuleBase
{
public:
	SkeletonModule();
	virtual ~SkeletonModule();
	void	AddMesh(Mesh* pMesh);


	void	SetSkeletonResource(shared_ptr<SkeletonResource> pRes,bool bGenerateObj = true);
private:
	void	GenerateSkeletonObj();
private:
	SkeletonObj* m_pSkeletonRoot;
	std::vector<Mesh*> m_MeshVec;
	shared_ptr<SkeletonResource> m_pSkeRes;
};

