#include "stdafx.h"
#include "Mesh.h"
#include "MeshResource.h"
#include "MaterialResource.h"
Mesh::Mesh()
	:m_bCpuSkin(false)
{
}


Mesh::~Mesh()
{
}

void Mesh::SetMeshResource(SmartPointer<MeshResource> pRes)
{
		m_pSharedMesh = pRes;
		m_pVertexData = pRes->m_VertexData.SmartPointerCast<VertexData>();
		m_pIndexData = pRes->m_IndexData;
}

SmartPointer<MeshResource> Mesh::GetMeshResource()
{
	return m_pSharedMesh;
}

bool Mesh::HasSkinInfo()
{
	return m_pSharedMesh->m_VertexData->nBoneNum > 0;
}

SmartPointer<ModuleBase> Mesh::Clone()
{
	SmartPointer<Mesh> pCloneMesh = SmartPointer<Mesh>(new Mesh);
	pCloneMesh->m_pSharedMaterial = m_pSharedMaterial;
	if (m_pSharedMaterial != nullptr)
	{
		if (m_pMaterialInstance != nullptr)
		{
			pCloneMesh->m_pMaterialInstance = m_pMaterialInstance->clone();
		}
		// = m_pSharedMaterial->clone();
	}
	pCloneMesh->m_bCpuSkin = m_bCpuSkin;
	//
	if (m_pSharedMesh->m_VertexData->nBoneNum > 0 && m_bCpuSkin == true)
	{
		pCloneMesh->m_pMeshInstance = m_pSharedMesh->clone();
	}
	else
	{
		pCloneMesh->m_pIndexData = m_pIndexData;
		pCloneMesh->m_pVertexData = m_pVertexData;
		pCloneMesh->m_pSharedMesh = m_pSharedMesh;
		pCloneMesh->m_pMeshInstance = m_pSharedMesh;
	}
	

	return pCloneMesh.get();
}
