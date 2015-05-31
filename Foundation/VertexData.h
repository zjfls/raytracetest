#pragma once
#include "RenderEnum.h"
#include "VertexData.h"
#include "Vector3.h"
#include "GameObjectBase.h"
using ZG::GameObjectBase;
class IndexData;
class FOUNDATION_API VertexData:public GameObjectBase
{
public:
	VertexData() :nBoneNum(0)
		, nNumVertex(0)
		, m_PrimitiveType(EPRIMITIVE_TRIANGLE)
	{};
	virtual ~VertexData();
	virtual void getBoundingMaxAndMin(Vector3& min,Vector3 max) = 0;
	int		GetVertexDataLength()const;
	struct VertexDataDesc
	{
		EnumVertexUseDesc usedesc;
		EnumVertexTypeDesc typedesc;
		unsigned int nOffset;//in byte
	};
	static int		GetTypeLength(const VertexDataDesc& desc);

public:
	std::vector<VertexData::VertexDataDesc> vecDataDesc;
	unsigned int nNumVertex;
	unsigned int nBoneNum;//每个顶点对应的骨头数量
	EDRAWPRIMITIVETYPE m_PrimitiveType;
};
class FOUNDATION_API MeshVertexData:public VertexData
{
public:
	MeshVertexData()
		:pData(nullptr)

	{

	}
	virtual ~MeshVertexData()
	{
		if (pData != nullptr)
		{
			delete[] (unsigned char*)pData;
			pData = nullptr;
		}

	}
	void* pData;


	virtual void getBoundingMaxAndMin( Vector3& min, Vector3 max);
	Vector3 GetPositionDataAt(int nIndex)
	{
		Vector3 vecPos;
		VertexDataDesc desc = vecDataDesc[0];
		float* pfData = (float*)pData;
		pfData = (float*)((char*)pfData + desc.nOffset + nIndex * GetVertexDataLength());
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
		pfData = (float*)((char*)pfData + desc.nOffset + nIndex * GetVertexDataLength());
		vecNormal.m_fx = *pfData;
		pfData++;
		vecNormal.m_fy = *pfData;
		pfData++;
		vecNormal.m_fz = *pfData;
		return vecNormal;
	}
	void ComputeTangent(const IndexData& indexData);
	unsigned int GetBuffLength() const;

	void*	GetElementData(int descIndex, int posIndex) const;
	
	
	


};

