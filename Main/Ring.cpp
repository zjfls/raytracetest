#include "stdafx.h"
#include "Ring.h"
#include "DynamicVertexData.h"
#include "MathDefine.h"
#include "Quaternion.h"
#include "Matrix33.h"
using namespace ZG;

ZG::Ring::~Ring()
{

}

void ZG::Ring::GeneratePolygon()
{
	if (m_fRadius <= m_fCircleRadius * 2)
	{
		return;
	}
	if (m_nSubdivide < 5)
	{
		return;
	}
	if (m_nCircleSubdivide < 3)
	{
		return;
	}
	if (m_pVertexData != nullptr)
	{
		//delete m_pVertexData;
		m_pVertexData = nullptr;
	}
	if (m_pIndexData != nullptr)
	{
		//delete m_pIndexData;
		m_pIndexData = nullptr;
	}
	//
	DynamicVertexData* dVertexData = new DynamicVertexData;
	VertexData::VertexDataDesc desc;
	desc.nOffset = 0;
	desc.typedesc = EVertexTypeFloat3;
	desc.usedesc = EVertexPosition;
	dVertexData->vecDataDesc.push_back(desc);
	m_pVertexData = dVertexData;

	dVertexData->m_nNumVertex = (m_nSubdivide + 1) * (m_nCircleSubdivide + 1);
	for (int i = 0; i < m_nSubdivide + 1; ++i)
	{
		float fAngle = 2 * PI / m_nSubdivide * i;
		for (int j = 0; j < m_nCircleSubdivide + 1; ++j)
		{
			float fCircleAngle = 2 * PI / m_nCircleSubdivide * j;
			Vector3 vPos;
			vPos.m_fy = 0.0f;
			vPos.m_fx = cos(fAngle) * m_fRadius;
			vPos.m_fz = sin(fAngle) * m_fRadius;

			//Vector3 curDir = vPos;
			//curDir.normalize();
			//Vector3 vertDir;
			//Matrix33 mat;
			//mat.RotAboutY(-fAngle - PI / 2);
			//vertDir = mat.GetForwardDir();
			Vector3 vOffset;
			vOffset.m_fz = 0.0f;
			vOffset.m_fx = cos(fCircleAngle) * m_fCircleRadius;
			vOffset.m_fy = sin(fCircleAngle) * m_fCircleRadius;

			Matrix33 mat;
			mat.RotAboutY(-fAngle);
			vOffset = vOffset * mat;
			vPos = vPos + vOffset;
			dVertexData->m_PositionData.push_back(vPos);
		}
	}
	std::vector<int> vecIndex;
	m_pIndexData = new IndexData;
	int nTriNum = m_nSubdivide * m_nCircleSubdivide * 2;
	m_pIndexData->indexNum = nTriNum * 3;
	for (int i = 0; i < m_nSubdivide; ++i)
	{
		for (int j = 0; j < m_nCircleSubdivide; ++j)
		{
			vecIndex.push_back(i * (m_nCircleSubdivide + 1) + j);
			vecIndex.push_back((i + 1) * (m_nCircleSubdivide + 1) + j);
			vecIndex.push_back(i * (m_nCircleSubdivide + 1) + j + 1);

			vecIndex.push_back(i * (m_nCircleSubdivide + 1) + j + 1);
			vecIndex.push_back((i + 1) * (m_nCircleSubdivide + 1) + j);
			vecIndex.push_back((i + 1) * (m_nCircleSubdivide + 1) + j + 1);
		}
	}

	//
	if (dVertexData->m_nNumVertex > 65535)
	{
		m_pIndexData->indexDesc = EIndexInt;
		m_pIndexData->pData = new int[nTriNum * 3];
		int* pData = (int*)m_pIndexData->pData;
		for (int i = 0; i < nTriNum * 3; ++i)
		{
			pData[i] = vecIndex[i];
			//std::cout <<"index:" << i << " = " << vecIndex[i] << std::endl;
		}
	}
	else
	{
		m_pIndexData->indexDesc = EIndexShort;
		m_pIndexData->pData = new unsigned short[nTriNum * 3];
		unsigned short* pData = (unsigned short*)m_pIndexData->pData;
		for (int i = 0; i < nTriNum * 3; ++i)
		{
			pData[i] = (unsigned short)vecIndex[i];
			//std::cout << "index:" << i << " = " << vecIndex[i];// << std::endl;
		}
		//std::cout << endl;
	}

}

ZG::Ring::Ring()
	:m_fRadius(100)
	, m_fCircleRadius(10)
	, m_nSubdivide(50)
	, m_nCircleSubdivide(5)
{

}



