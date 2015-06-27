#include "stdafx.h"
#include "Cylinder.h"
#include "DynamicVertexData.h"
#include "MathDefine.h"
#include "Vector3.h"
#include <vector>
#include "IWorldObj.h"
#include "MaterialResource.h"

ZG::Cylinder::Cylinder()
	:m_fRadius(1.0f)
	, m_fHeight(5.0f)
	, m_nSubdivide(10)
{

}

ZG::Cylinder::~Cylinder()
{

}

void ZG::Cylinder::GeneratePolygon()
{
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
	if (m_nSubdivide < 3 || m_fHeight <= 0.1f || m_fRadius <= 0.1f)
	{
		return;
	}
	//
	DynamicVertexData* dVertexData = new DynamicVertexData;
	VertexData::VertexDataDesc desc;
	desc.nOffset = 0;
	desc.typedesc = EVertexTypeFloat3;
	desc.usedesc = EVertexPosition;
	dVertexData->vecDataDesc.push_back(desc);
	m_pVertexData = dVertexData;
	
	dVertexData->m_nNumVertex = (m_nSubdivide + 1) * 2 + 2;
	for (int i = 0; i < m_nSubdivide + 1; ++i)
	{
		float phi = 2 * PI / m_nSubdivide * i;
		float x = m_fRadius * cos(phi);
		float z = m_fRadius * sin(phi);
		float y = 0.0f;
		dVertexData->m_PositionData.push_back(Vector3(x, y, z));
	}
	for (int i = 0; i < m_nSubdivide + 1;++i)
	{
		float phi = 2 * PI / m_nSubdivide * i;
		float x = m_fRadius * cos(phi);
		float z = m_fRadius * sin(phi);
		float y = m_fHeight;
		dVertexData->m_PositionData.push_back(Vector3(x, y, z));
	}
	dVertexData->m_PositionData.push_back(Vector3(0.0f, 0.0f, 0.0f));
	dVertexData->m_PositionData.push_back(Vector3(0.0f, m_fHeight, 0.0f));
	//
	//
	std::vector<int> vecIndex;
	m_pIndexData = new IndexData;
	int nTriNum = m_nSubdivide * 4;
	m_pIndexData->indexNum = m_nSubdivide * 4 * 3;
	for (int i = 0; i < m_nSubdivide; ++i)
	{
		vecIndex.push_back((m_nSubdivide + 1) * 2);
		vecIndex.push_back(i + 1);
		vecIndex.push_back(i);
	}
	//
	for (int i = 0; i < m_nSubdivide; ++i)
	{
		vecIndex.push_back((m_nSubdivide + 1) * 2 + 1);
		vecIndex.push_back(i + m_nSubdivide + 2);
		vecIndex.push_back(i + m_nSubdivide + 1);
	}
	//
	for (int i = 0; i < m_nSubdivide; ++i)
	{
		vecIndex.push_back(i);
		vecIndex.push_back(i + m_nSubdivide + 1);
		vecIndex.push_back(i + m_nSubdivide + 2);
		//vecIndex.push_back(i + m_nSubdivide + 1);
		//vecIndex.push_back(i + m_nSubdivide + 2);
		//vecIndex.push_back(i + 1);
		vecIndex.push_back(i);
		vecIndex.push_back(i + m_nSubdivide + 2);
		vecIndex.push_back(i+1);
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


