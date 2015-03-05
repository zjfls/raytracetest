#pragma once
#include "IResource.h"

struct stVertexData
{
	void* pData;
	enum EnumVertexDesc
	{
		EVertexInvalid = 0,
		EVertexPosition,
		EVertexNormal,
		EVertexTangent,
		EVertexColor,
		EVertexUV
	};
	struct VertexDataDesc
	{
		EnumVertexDesc desc;
		int nOffset;//in byte
	};
	std::vector<VertexDataDesc> vecDataDesc;
};
struct stIndexData
{
	void* pData;
	enum EnumIndexDesc
	{
		EIndexInvalid = 0,
		EIndexInt,
		EIndexShort
	};
	EnumIndexDesc indexDesc;

};
class MeshResource:public IResource
{
public:
	MeshResource();
	~MeshResource();


	stVertexData m_VertexData;
	stIndexData m_IndexData;
};

