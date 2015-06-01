#pragma once
#include "IResource.h"
#include "ResourceManager.h"
#include "VertexData.h"
#include "IndexData.h"
#include "Singleton.h"
#include "SmartPointer.h"
using ZG::SmartPointer;

//

class RESOURCE_API MeshResource :public IResource
{
public:
	MeshResource();
	~MeshResource();
	//Vector3 GetPositionDataAt(int nIndex);
	//Vector3	GetNormalDataAt(int nIndex);
	SmartPointer<MeshResource> clone();
	SmartPointer<MeshVertexData> m_VertexData;
	SmartPointer<IndexData> m_IndexData;
	friend class ResourceManager<MeshResource>;
};
extern template  class RESOURCE_API  Singleton<ResourceManager<MeshResource>>;


