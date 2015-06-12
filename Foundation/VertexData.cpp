#include "stdafx.h"
#include "VertexData.h"
#include "RenderEnum.h"
#include "Vector3.h"
#include "Vector2.h"
#include "IndexData.h"
#include <iostream>
#include "MathDefine.h"
#include "VertexIndexDataEventProxy.h"
#include "AABBBox.h"
VertexData::~VertexData()
{
	VertexDataEventArg arg;
	arg.m_pVertexData = this;
	Event<VertexDataEventArg>* e = VertexIndexDataEventProxy::GetInstance()->getEvent<VertexDataEventArg>("VERTEXDATADELETE");
	(*e)(arg);
}
//
void* MeshVertexData::GetElementData(int descIndex, int posIndex) const
{
	if (descIndex >= vecDataDesc.size())
	{
		return nullptr;
	}
	if (posIndex >= nNumVertex)
	{
		return nullptr;
	}
	VertexDataDesc desc = vecDataDesc[descIndex];
	int nOffset = desc.nOffset;
	int nUnitLength = GetTypeLength(desc);

	return (unsigned char*)pData + posIndex * GetVertexDataLength() + nOffset;
}

int VertexData::GetTypeLength(const VertexDataDesc& desc)
{
	switch (desc.typedesc)
	{
		case EVertexTypeFloat1:
		{
			return 4;
		}
		break;
		case EVertexTypeFloat2:
		{
			return 8;
		}
		break;
		case EVertexTypeFloat3:
		{
			return 12;
		}
		break;
		case EVertexTypeFloat4:
		{
			return 16;
		}
		break;
		case EVertexTypeUByte4:
		{
			return 4;
		}
	}
	return 0;

}

int VertexData::GetVertexDataLength() const
{
	int nLength = 0;
	for each (VertexDataDesc desc in vecDataDesc)
	{
		nLength += GetTypeLength(desc);
	}
	return nLength;
}

unsigned int MeshVertexData::GetBuffLength() const
{
	return GetVertexDataLength() * nNumVertex;
}

void MeshVertexData::ComputeTangent(const IndexData& iData)
{
	int nNormalIndex = -1;
	int nUVIndex = -1;
	int nPosition = -1;
	int index = 0;
	for each (VertexDataDesc desc in vecDataDesc)
	{
		if (desc.usedesc == EVertexTangent)
		{
			return;
		}
		if (desc.usedesc == EVertexNormal)
		{
			nNormalIndex = index;
		}
		if (desc.usedesc == EVertexUV)
		{
			nUVIndex = index;
		}
		if (desc.usedesc == EVertexPosition)
		{
			nPosition = index;
		}
		index++;
	}
	int nCount = vecDataDesc.size();
	VertexDataDesc desc = vecDataDesc[nCount - 1];
	int nOffset = desc.nOffset;
	int nLength = GetTypeLength(desc);
	nOffset += nLength;



	VertexDataDesc tangentdesc;
	tangentdesc.nOffset = nOffset;
	tangentdesc.usedesc = EVertexTangent;
	tangentdesc.typedesc = EVertexTypeFloat3;
	
	//
	int nIndexSize = iData.indexNum;
	int nTriangleNum = nIndexSize / 3;


	Vector3* tan1 = new Vector3[nNumVertex];
	Vector3* tan2 = new Vector3[nNumVertex];
	Vector3* tangent = new Vector3[nNumVertex];
	memset(tan1, 0, sizeof(Vector3) * nNumVertex);
	memset(tan2, 0, sizeof(Vector3) * nNumVertex);
	memset(tangent, 0, sizeof(Vector3) * nNumVertex);

	for (int i = 0; i < nTriangleNum; ++i)
	{
		int i1 = iData.GetIndexAt(i, 0);
		int i2 = iData.GetIndexAt(i, 1);
		int i3 = iData.GetIndexAt(i, 2);
		
		float* pPos1 = (float*)GetElementData(nPosition, i1);
		float* pPos2 = (float*)GetElementData(nPosition, i2);
		float* pPos3 = (float*)GetElementData(nPosition, i3);
		float* pUV1 = (float*)GetElementData(nUVIndex, i1);
		float* pUV2 = (float*)GetElementData(nUVIndex, i2);
		float* pUV3 = (float*)GetElementData(nUVIndex, i3);

		//
		Vector3 vecPos1 = Vector3(*pPos1, *(pPos1 + 1), *(pPos1 + 2));
		Vector3 vecPos2 = Vector3(*pPos2, *(pPos2 + 1), *(pPos2 + 2));
		Vector3 vecPos3 = Vector3(*pPos3, *(pPos3 + 1), *(pPos3 + 2));
		Vector2 vecUV1 = Vector2(*pUV1, *(pUV1 + 1));
		Vector2 vecUV2 = Vector2(*pUV2, *(pUV2 + 1));
		Vector2 vecUV3 = Vector2(*pUV3, *(pUV3 + 1));
		float x1 = vecPos2.m_fx - vecPos1.m_fx;
		float x2 = vecPos3.m_fx - vecPos1.m_fx;
		float y1 = vecPos2.m_fy - vecPos1.m_fy;
		float y2 = vecPos3.m_fy - vecPos1.m_fy;
		float z1 = vecPos2.m_fz - vecPos1.m_fz;
		float z2 = vecPos3.m_fz - vecPos1.m_fz;

		float s1 = vecUV2.m_fx - vecUV1.m_fx;
		float s2 = vecUV3.m_fx - vecUV1.m_fx;
		float t1 = vecUV2.m_fy - vecUV1.m_fy;
		float t2 = vecUV3.m_fy - vecUV1.m_fy;


		//float r = 1.0f / (s1 * t2 - s2 * t1);

		float div = s1 * t2 - s2 * t1;
		float r = div == 0.0f ? 0.0f : 1.0f / div;
		//
		Vector3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
			(t2 * z1 - t1 * z2) * r);
		Vector3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
			(s1 * z2 - s2 * z1) * r);


		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;

		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
	}
	//
	for (long a = 0; a < nNumVertex; a++)
	{
		float* pNormal = (float*)GetElementData(nNormalIndex, a);
		Vector3 n = *((Vector3*)pNormal);
		//const Vector3& n = normal[a];
		const Vector3& t = tan1[a];

		// Gram-Schmidt orthogonalize
		//tangent[a] = (t - n * Dot(n, t)).Normalize();

		tangent[a] = (n * n.dot(t) - t).normalize();

		// Calculate handedness
		//tangent[a].w = (Dot(Cross(n, t), tan2[a]) < 0.0F) ? -1.0F : 1.0F;
	}
	vecDataDesc.push_back(tangentdesc);
	//
	unsigned char* pNewData = new unsigned char[GetVertexDataLength() * nNumVertex];
	int nVertexSize = GetVertexDataLength();
	int nVertexSizeOld = nVertexSize - 12;
	for (int i = 0; i < nNumVertex; ++i)
	{
		memcpy(pNewData + i * nVertexSize, (unsigned char*)pData + i * nVertexSizeOld, nVertexSizeOld);
		memcpy(pNewData + i * nVertexSize + nVertexSizeOld, &tangent[i], 12);
	}
	delete[](unsigned char*)pData;
	pData = pNewData;
	delete[] tan1;
	delete[] tan2;
}

void MeshVertexData::getBoundingMaxAndMin( Vector3& min, Vector3& max)
{
	if (m_pAABB == nullptr)
	{
		m_pAABB = new AABBBox;
	}
	else
	{
		min = m_pAABB->m_Min;
		max = m_pAABB->m_Max;
		return;
	}
	min.m_fx = MAXFLOAT;
	min.m_fy = MAXFLOAT;
	min.m_fz = MAXFLOAT;
	max.m_fx = MINFLOAT;
	max.m_fy = MINFLOAT;
	max.m_fz = MINFLOAT;
	//to do
	for (int i = 0; i < nNumVertex; ++i)
	{
		Vector3 v = GetPositionDataAt(i);
		if (v.m_fx < min.m_fx)
		{
			min.m_fx = v.m_fx;
		}
		if (v.m_fy < min.m_fy)
		{
			min.m_fy = v.m_fy;
		}
		if (v.m_fz < min.m_fz)
		{
			min.m_fz = v.m_fz;
		}

		if (v.m_fx > max.m_fx)
		{
			max.m_fx = v.m_fx;
		}
		if (v.m_fy > max.m_fy)
		{
			max.m_fy = v.m_fy;
		}
		if (v.m_fz > max.m_fz)
		{
			max.m_fz = v.m_fz;
		}
	}
	m_pAABB->m_Min = min;
	m_pAABB->m_Max = max;
}

