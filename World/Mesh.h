#pragma once
#include "Geometry.h"



class MeshResource;
class WORLD_API Mesh :public Geometry
{
public:
	Mesh();
	virtual ~Mesh();


	SmartPointer<MeshResource> GetMeshResource();

	void SetMeshResource(SmartPointer<MeshResource> pRes);
	bool	HasSkinInfo();
	virtual SmartPointer<ModuleBase> Clone();
private:
	//
	SmartPointer<MeshResource> m_pMeshInstance;
	SmartPointer<MeshResource> m_pSharedMesh;
public:
	bool m_bCpuSkin;
};

