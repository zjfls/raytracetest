#pragma once
#include "ModuleBase.h"
#include "AnimationModule.h"
namespace ZG
{
	class SkeletonObj;
	class Mesh;
	class SkeletonResource;
	class MAIN_API SkeletonModule :public AnimationModule
	{
	public:
		SkeletonModule();
		virtual ~SkeletonModule();
		void	AddMesh(SmartPointer<Mesh> pMesh);
		virtual SmartPointer<ModuleBase> Clone();
		virtual void Update();
		void	GenerateSkeletonArchi();
		SkeletonResource*	GetSkeletonRes(){ return m_SkeletonRes.get(); };
		void				SetSkeletonRes(SkeletonResource* pRes){ m_SkeletonRes = pRes; };
		//void	SetSkeletonResource(SmartPointer<SkeletonResource> pRes,bool bGenerateObj = true);
	private:
		void	GenerateSkeletonObj();
	private:
		//SkeletonObj* m_pSkeletonRoot;
		std::vector<SmartPointer<Mesh>> m_MeshVec;
		SmartPointer<SkeletonObj> m_pSkeletonRoot;
		SmartPointer<SkeletonResource> m_SkeletonRes;
		string m_strSkeleton;
	};

}