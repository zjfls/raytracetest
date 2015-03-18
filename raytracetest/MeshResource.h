#pragma once
#include "IResource.h"
#include "ResourceMananger.h"
#include "Geometry.h"

class MeshResource:public IResource
{
public:
	MeshResource();
	~MeshResource();
	//Vector3 GetPositionDataAt(int nIndex);
	//Vector3	GetNormalDataAt(int nIndex);

	stVertexData m_VertexData;
	stIndexData m_IndexData;
	friend class ResourceManager<MeshResource>;
};

