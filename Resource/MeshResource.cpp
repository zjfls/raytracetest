#include "stdafx.h"
#include "MeshResource.h"
#include "ResourceManager.h"
template class RESOURCE_API Singleton<ResourceManager<MeshResource>>;
template<> shared_ptr<ResourceManager<MeshResource>> Singleton<ResourceManager<MeshResource>>::_instance = nullptr;

MeshResource::MeshResource() 
{
}


MeshResource::~MeshResource()
{
}

shared_ptr<MeshResource> MeshResource::clone()
{
	shared_ptr<MeshResource> pCloneMeshRes(new MeshResource);
	*pCloneMeshRes = *this;
	pCloneMeshRes->m_IndexData.pData = new unsigned char[m_IndexData.GetBuffLength()];
	memcpy((void*)pCloneMeshRes->m_IndexData.pData, (void*)m_IndexData.pData, m_IndexData.GetBuffLength());
	pCloneMeshRes->m_VertexData.pData = new unsigned char[m_VertexData.GetBuffLength()];
	memcpy((void*)pCloneMeshRes->m_VertexData.pData, (void*)m_VertexData.pData, m_VertexData.GetBuffLength());
	return pCloneMeshRes;
}

//Vector3 MeshResource::GetPositionDataAt(int nIndex)
//{
//	return m_VertexData.GetPositionDataAt(nIndex);
//}
//
//Vector3 MeshResource::GetNormalDataAt(int nIndex)
//{
//	return m_VertexData.GetPositionDataAt(nIndex);
//}