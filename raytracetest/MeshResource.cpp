#include "stdafx.h"
#include "MeshResource.h"
#include "ResourceMananger.h"
ResourceMananger<MeshResource>* Singleton<ResourceMananger<MeshResource>>::_instance = nullptr;


MeshResource::MeshResource()
{
}


MeshResource::~MeshResource()
{
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
