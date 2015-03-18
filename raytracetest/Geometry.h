#pragma once
#include "IRenderable.h"
struct stVertexData
{
	stVertexData()
		:pData(nullptr)
		, nBoneNum(0)
		, nNumVertex(0)
	{

	}
	~stVertexData()
	{
		if (pData != nullptr)
		{
			delete[] pData;
			pData = nullptr;
		}

	}
	void* pData;
	enum EnumVertexTypeDesc
	{
		EVertexTypeInvalid = 0,
		EVertexTypeFloat1,
		EVertexTypeFloat2,
		EVertexTypeFloat3,
		EVertexTypeFloat4,
		EVertexTypeByte4
	};
	enum EnumVertexUseDesc
	{
		EVertexInvalid = 0,
		EVertexPosition = 1 << 1,
		EVertexNormal = 1 << 2,
		EVertexTangent = 1 << 3,
		EVertexColor = 1 << 4,
		EVertexUV = 1 << 5,
		EVertexBlendIndex = 1 << 6,
		EVertexBlendWeight = 1 << 7
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
	//Ĭ��normal�����ǵ�2��
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



	void*	GetElementData(int descIndex, int posIndex) const;
	int		GetVertexDataLength()const;
	int		GetTypeLength(const VertexDataDesc& desc) const;
	std::vector<VertexDataDesc> vecDataDesc;
	unsigned int nNumVertex;
	unsigned int nBoneNum;//ÿ�������Ӧ�Ĺ�ͷ����

};
struct stIndexData
{
	stIndexData()
		:pData(nullptr)
		, indexNum(0)
	{

	}
	void* pData;
	~stIndexData()
	{
		if (pData != nullptr)
		{
			delete[] pData;
			pData = nullptr;
		}

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
class Geometry :
	public IRenderable
{
public:
	Geometry();
	virtual ~Geometry();

protected:
	stVertexData* m_pVertexData;
	stIndexData* m_pIndexData;
};
