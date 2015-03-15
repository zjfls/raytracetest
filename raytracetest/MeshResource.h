#pragma once
#include "IResource.h"
#include "ResourceMananger.h"

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
		unsigned int nOffset;//in byte
	};
	Vector3 GetPositionDataAt(int nIndex)
	{
		Vector3 vecPos;
		VertexDataDesc desc = vecDataDesc[0];
		float* pfData = (float*)pData;
		pfData = pfData + desc.nOffset + nIndex * 3;
		vecPos.m_fx = *pfData;
		pfData++;
		vecPos.m_fy = *pfData;
		pfData++;
		vecPos.m_fz = *pfData;
		return vecPos;
	}
	//默认normal描述是第2个
	Vector3 GetNormalDataAt(int nIndex)
	{
		Vector3 vecNormal;
		VertexDataDesc desc = vecDataDesc[1];
		float* pfData = (float*)pData;
		pfData = pfData + desc.nOffset + nIndex * 3;
		vecNormal.m_fx = *pfData;
		pfData++;
		vecNormal.m_fy = *pfData;
		pfData++;
		vecNormal.m_fz = *pfData;
		return vecNormal;
	}
	~stVertexData()
	{
		delete[] pData;
		pData = nullptr;
	}


	void*	GetElementData(int descIndex, int posIndex) const;
	int		GetVertexDataLength()const;
	int		GetTypeLength(const VertexDataDesc& desc) const;
	std::vector<VertexDataDesc> vecDataDesc;
	unsigned int nNumVertex;
	
};
struct stIndexData
{
	void* pData;
	~stIndexData()
	{
		delete[] pData;
		pData = nullptr;
	}
	enum EnumIndexDesc
	{
		EIndexInvalid = 0,
		EIndexInt,
		EIndexShort
	};
	EnumIndexDesc indexDesc;
	int indexNum;

};
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

