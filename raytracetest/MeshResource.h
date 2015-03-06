#pragma once
#include "IResource.h"

struct stVertexData
{
	void* pData;
	enum EnumVertexTypeDesc
	{
		EVertexTypeInvalid = 0,
		EVertexTypeFloat1,
		EVertexTypeFloat2,
		EVertexTypeFloat3,
		EVertexTypeFloat4
	};
	enum EnumVertexUseDesc
	{
		EVertexInvalid = 0,
		EVertexPosition = 1 << 1 ,
		EVertexNormal = 1 << 2,
		EVertexTangent = 1 << 3,
		EVertexColor = 1 << 4,
		EVertexUV = 1 << 5
	};
	struct VertexDataDesc
	{
		EnumVertexUseDesc usedesc;
		EnumVertexTypeDesc typedesc;
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

