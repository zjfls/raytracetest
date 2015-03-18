#include "stdafx.h"
#include "Mesh.h"
#include "MeshResource.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::SetMeshResource(shared_ptr<MeshResource> pRes)
{
		m_pResource = pRes;
		m_pVertexData = &pRes->m_VertexData;
		m_pIndexData = &pRes->m_IndexData;
}

shared_ptr<MeshResource> Mesh::GetMeshResource()
{
	return m_pResource;
}

bool Mesh::HasSkinInfo() const
{
	return m_pVertexData->nBoneNum > 0;
}
