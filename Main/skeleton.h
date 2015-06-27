#pragma once
#include "ModuleBase.h"
#include "AnimationModule.h"
#include "MeshResource.h"

namespace ZG
{
	class SkeletonObj;
	class Mesh;
	class SkeletonResource;
	class SkinMatrixInfo;
	class MAIN_API SkeletonModule :public AnimationModule
	{
	public:
		SkeletonModule();
		virtual ~SkeletonModule();
		void	AddMesh(SmartPointer<Mesh> pMesh);
		virtual SmartPointer<ModuleBase> Clone();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		void OnStart() override;
		void	GenerateSkeletonArchi();
		SkeletonResource*	GetSkeletonRes(){ return m_SkeletonRes.get(); };
		void				SetSkeletonRes(SkeletonResource* pRes);

		
		bool PlayAnimation(AnimationTrack* pTrack) override;
		bool BindAnimation(AnimationTrack* pTrack) override;
		//void	SetSkeletonResource(SmartPointer<SkeletonResource> pRes,bool bGenerateObj = true);
	protected:
		void				OnInitialize() override;
	private:
		void	GenerateSkeletonObj();
		void	GenerateSkeletonIndexMap();
	private:
		//SkeletonObj* m_pSkeletonRoot;
		std::vector<SmartPointer<Mesh>> m_MeshVec;
		SmartPointer<SkeletonObj> m_pSkeletonRoot;
		SmartPointer<SkeletonResource> m_SkeletonRes;

		SmartPointer<SkinMatrixInfo> m_SkinMatrix;
		std::map<std::string, SkeletonObj*> m_mapNameToSkeletonObj;
		
		string m_strSkeleton;
	public:
		std::map<int, SkeletonObj*> m_mapSkeletonObj;
	};

}