#pragma once
#include "IResource.h"
#include "ResourceManager.h"
#include "VertexData.h"
#include "IndexData.h"
#include "Singleton.h"

class RESOURCE_API MeshResource :public IResource
{
public:
	MeshResource();
	~MeshResource();
	//Vector3 GetPositionDataAt(int nIndex);
	//Vector3	GetNormalDataAt(int nIndex);
	shared_ptr<MeshResource> clone();
	MeshVertexData m_VertexData;
	IndexData m_IndexData;
	friend class ResourceManager<MeshResource>;
};
extern template  class RESOURCE_API  Singleton<ResourceManager<MeshResource>>;


