#pragma once
class VertexData
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



	void*	GetElementData(int descIndex, int posIndex) const;
	int		GetVertexDataLength()const;
	int		GetTypeLength(const VertexDataDesc& desc) const;
	std::vector<VertexDataDesc> vecDataDesc;
	unsigned int nNumVertex;
	unsigned int nBoneNum;//每个顶点对应的骨头数量

};

