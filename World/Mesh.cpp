#include "stdafx.h"
#include "Mesh.h"
#include "MeshResource.h"

Mesh::Mesh()
	:m_bCpuSkin(false)
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

ModuleBase* Mesh::Clone()
{
	Mesh* pCloneMesh = new Mesh;
	pCloneMesh->m_pMaterial = m_pMaterial;
	pCloneMesh->m_bCpuSkin = m_bCpuSkin;
	//
	if (m_pResource->m_VertexData.nBoneNum > 0 && m_bCpuSkin == true)
	{

	}
	else
	{
		pCloneMesh->m_pIndexData = m_pIndexData;
		pCloneMesh->m_pVertexData = m_pVertexData;
		pCloneMesh->m_pResource = m_pResource;
	}
	

	return pCloneMesh;
}
