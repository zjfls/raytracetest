#pragma once
#include "RenderEnum.h"
#include "VertexData.h"
#include "Vector3.h"
class FOUNDATION_API VertexData
{
public:
	VertexData()
		:pData(nullptr)
		, nBoneNum(0)
		, nNumVertex(0)
	{

	}
	~VertexData()
	{
		if (pData != nullptr)
		{
			delete[] (unsigned char*)pData;
			pData = nullptr;
		}

	}
	void* pData;

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

	unsigned int GetBuffLength() const;

	void*	GetElementData(int descIndex, int posIndex) const;
	int		GetVertexDataLength()const;
	static int		GetTypeLength(const VertexDataDesc& desc);
	std::vector<VertexData::VertexDataDesc> vecDataDesc;
	unsigned int nNumVertex;
	unsigned int nBoneNum;//每个顶点对应的骨头数量

};

