#pragma once
#include "Geometry.h"



class MeshResource;
class WORLD_API Mesh :public Geometry
{
public:
	Mesh();
	virtual ~Mesh();


	shared_ptr<MeshResource> GetMeshResource();

	void SetMeshResource(shared_ptr<MeshResource> pRes);
	bool	HasSkinInfo() const;
	virtual ModuleBase* Clone();
private:
	//
	shared_ptr<MeshResource> m_pMeshInstance;
	shared_ptr<MeshResource> m_pSharedMesh;
public:
	bool m_bCpuSkin;
};

