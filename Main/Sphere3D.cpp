#include "stdafx.h"
#include "Sphere3D.h"
#include "DynamicVertexData.h"
#include "MathDefine.h"
#include <iostream>
#include "MaterialResource.h"
#include "IWorldObj.h"

Sphere3D::Sphere3D()
	:m_nSubdivide(10)
{
}


Sphere3D::~Sphere3D()
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
	
}

void Sphere3D::GeneratePolygon()
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
	if (m_nSubdivide < 3)
	{
		return;
	}
	DynamicVertexData* dVertexData = new DynamicVertexData;
	VertexData::VertexDataDesc desc;
	desc.nOffset = 0;
	desc.typedesc = EVertexTypeFloat3;
	desc.usedesc = EVertexPosition;
	dVertexData->vecDataDesc.push_back(desc);
	m_pVertexData = dVertexData;
	dVertexData->m_nNumVertex = (m_nSubdivide + 1) * (m_nSubdivide + 1);
	//
	for (int i = 0; i <= m_nSubdivide + 1; ++i)
	{
		for (int j = 0; j < m_nSubdivide + 1; ++j)
		{
			float seta = PI / m_nSubdivide * i;
			float phi = 2 * PI / m_nSubdivide * j;

			float y = m_fRadius * cos(seta);
			float z = m_fRadius * sin(seta) * sin(phi);
			float x = m_fRadius * sin(seta) * cos(phi);
			Vector3 v(x, y, z);
			dVertexData->m_PositionData.push_back(v);
		}
	}
	//
	m_pIndexData = nullptr;


	int nTriNum = m_nSubdivide * (m_nSubdivide - 1) * 2;
	std::vector<int> vecIndex;
	for (int i = 0; i < m_nSubdivide; ++i)
	{
		for (int j = 0; j < m_nSubdivide; ++j)
		{
			if (i == 0)
			{
				vecIndex.push_back(j);
				vecIndex.push_back(j + m_nSubdivide + 2);
				vecIndex.push_back(j + m_nSubdivide + 1);
			}
			else if (i == m_nSubdivide - 1)
			{
				vecIndex.push_back(j + i * (m_nSubdivide + 1));
				vecIndex.push_back(j + i * (m_nSubdivide + 1) + 1);
				vecIndex.push_back(j + (i + 1) * (m_nSubdivide + 1));
			}
			else
			{
				vecIndex.push_back(j + i * (m_nSubdivide + 1));
				vecIndex.push_back(j + (i + 1) * (m_nSubdivide + 1) + 1);
				vecIndex.push_back(j + (i + 1) * (m_nSubdivide + 1));
				vecIndex.push_back(j + i * (m_nSubdivide + 1));
				vecIndex.push_back(j + i * (m_nSubdivide + 1) + 1);
				vecIndex.push_back(j + (i + 1) * (m_nSubdivide + 1) + 1);
			}
		}
	}



	m_pIndexData = new IndexData;
	m_pIndexData->indexNum = nTriNum * 3;
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

//Sphere3DCreator::Sphere3DCreator()
//{
//
//}
//
//Sphere3DCreator::~Sphere3DCreator()
//{
//
//}
//
//ModuleBase* Sphere3DCreator::CreateModule()
//{
//	return new Sphere3D;
//}
