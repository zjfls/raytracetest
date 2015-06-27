#pragma once
#include "Geometry.h"

namespace ZG
{

	class MeshResource;
	class MAIN_API Mesh :public Geometry
	{
	public:
		Mesh();
		virtual ~Mesh();


		SmartPointer<MeshResource> GetMeshResource();

		void SetMeshResource(SmartPointer<MeshResource> pRes);
		bool	HasSkinInfo();
		virtual SmartPointer<ModuleBase> Clone();
		void	CopyFrom(Mesh* pMesh);
		void	SetCpuSkin(bool bCpuSkin);
	private:
		//
		SmartPointer<MeshResource> m_pMeshInstance;
		SmartPointer<MeshResource> m_pSharedMesh;
	public:
		bool m_bCpuSkin;
	};

}