#include "stdafx.h"
#include "Cone.h"
#include "DynamicVertexData.h"
#include "MathDefine.h"
#include "MaterialResource.h"
#include "IWorldObj.h"

ZG::Cone::Cone()
	:m_fRadius(30.0f)
	, m_fHeight(50.0f)
	, m_nSubdivide(100)
{

}

ZG::Cone::~Cone()
{

}

void ZG::Cone::GeneratePolygon()
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

	dVertexData->m_nNumVertex = (m_nSubdivide + 1) + 2;
	for (int i = 0; i < m_nSubdivide + 1; ++i)
	{
		float phi = 2 * PI / m_nSubdivide * i;
		float x = m_fRadius * cos(phi);
		float z = m_fRadius * sin(phi);
		float y = 0.0f;
		dVertexData->m_PositionData.push_back(Vector3(x, y, z));
	}

	dVertexData->m_PositionData.push_back(Vector3(0.0f, 0.0f, 0.0f));
	dVertexData->m_PositionData.push_back(Vector3(0.0f, m_fHeight, 0.0f));
	//
	//
	std::vector<int> vecIndex;
	m_pIndexData = new IndexData;
	int nTriNum = m_nSubdivide * 2;
	m_pIndexData->indexNum = nTriNum * 3;
	for (int i = 0; i < m_nSubdivide; ++i)
	{
		vecIndex.push_back((m_nSubdivide + 1));
		vecIndex.push_back(i);
		vecIndex.push_back(i+1);
	}
	//
	for (int i = 0; i < m_nSubdivide; ++i)
	{
		vecIndex.push_back(i);
		vecIndex.push_back(m_nSubdivide + 2);
		vecIndex.push_back(i + 1);

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
