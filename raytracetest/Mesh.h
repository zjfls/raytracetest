#pragma once
#include "Geometry.h"



class MeshResource;
class Mesh:public Geometry
{
public:
	Mesh();
	virtual ~Mesh();


	shared_ptr<MeshResource> GetMeshResource();

	void SetMeshResource(shared_ptr<MeshResource> pRes);
	bool	HasSkinInfo() const;

private:
	//
	shared_ptr<MeshResource> m_pResource;
};

