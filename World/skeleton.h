#pragma once
#include "ModuleBase.h"
namespace ZG
{
	class SkeletonObj;
	class Mesh;
	class SkeletonResource;
	class WORLD_API SkeletonModule :public ModuleBase
	{
	public:
		SkeletonModule();
		virtual ~SkeletonModule();
		void	AddMesh(SmartPointer<Mesh> pMesh);


		//void	SetSkeletonResource(SmartPointer<SkeletonResource> pRes,bool bGenerateObj = true);
	private:
		void	GenerateSkeletonObj();
	private:
		SkeletonObj* m_pSkeletonRoot;
		std::vector<SmartPointer<Mesh>> m_MeshVec;
		SmartPointer<SkeletonResource> m_pSkeRes;
		string m_strSkeleton;
	};

}