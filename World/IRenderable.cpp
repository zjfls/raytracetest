#include "stdafx.h"
#include "IRenderable.h"
#include "CommonDef.h"
#include "BoundingBase.h"
#include "AABBBox.h"
#include "ResourceManager.h"
#include "MaterialResource.h"
#include "IWorldObj.h"
#include "Transform.h"
#include "Matrix44.h"
#include "Vector4.h"


IRenderable::IRenderable()
	:m_pVertexData(nullptr)
	, m_pIndexData(nullptr)
	, m_pSharedMaterial(nullptr)
	, m_pMaterialInstance(nullptr)
	, m_pBounding(nullptr)
{
	
}


IRenderable::~IRenderable()
{
	if (m_pBounding != nullptr)
	{
		delete m_pBounding;
		m_pBounding = nullptr;
	}
}

void IRenderable::Update()
{
	if (m_bTransformUpdated == true)
	{
		if (m_pBounding == nullptr)
		{
			BuildBoundingVolume();
		}
		Matrix44 mat = m_pOwnerObj->m_pTransform->GetWorldMatrix();
		Vector4 vMin, vMax;
		AABBBox* pBox = dynamic_cast<AABBBox*>(m_pBounding);
		if (pBox != nullptr)
		{
			*pBox = *m_pVertexData->m_pAABB;
			pBox->Transform(mat);
		}
		m_bTransformUpdated = false;
	}
}

SmartPointer<MaterialResource> IRenderable::GetDefaultMaterial()
{
	return ResourceManager<MaterialResource>::GetInstance()->GetResource("GAMEDEFAULTMATERIAL");
}

void IRenderable::BuildBoundingVolume()
{
	if (m_pBounding != nullptr)
	{
		delete m_pBounding;
		m_pBounding = nullptr;
	}
	Vector3 vecMax, vecMin;
	if (m_pVertexData != nullptr)
	{
		if (m_pBounding != nullptr)
		{
			delete m_pBounding;
		}
		m_pVertexData->getBoundingMaxAndMin(vecMin, vecMax);
		AABBBox* pBox = new AABBBox();
		m_pBounding = pBox;
		pBox->m_Max = vecMax;
		pBox->m_Min = vecMin;


		if (m_pOwnerObj != nullptr)
		{
			Matrix44 mat = m_pOwnerObj->m_pTransform->GetWorldMatrix();
			Vector4 vMin,vMax;
			vMin.Vector3ToPoint(pBox->m_Min);
			vMax.Vector3ToPoint(pBox->m_Max);
			vMin = vMin * mat;
			vMax = vMax * mat;
			pBox->m_Max = vMax;
			pBox->m_Min = vMin;
		}
	}
}

SmartPointer<MaterialResource> IRenderable::GetMaterialInstance()
{
	if (m_pMaterialInstance == nullptr)
	{
		if (m_pSharedMaterial != nullptr)
		{
			m_pMaterialInstance = m_pSharedMaterial->clone();
		}
	}
	return m_pMaterialInstance;
}

SmartPointer<MaterialResource> IRenderable::getRenderMaterial()
{
	if (m_pMaterialInstance != nullptr)
	{
		return m_pMaterialInstance;
	}
	return m_pSharedMaterial;
}

ZG::Triangle ZG::IRenderable::GetTriangle(int nTriIndex) const
{
	Triangle tri;
	if (m_pVertexData == nullptr)
	{
		return tri;
	}
	if (m_pIndexData == nullptr)
	{
		if (nTriIndex * 3 > m_pVertexData->nNumVertex)
		{
			return tri;
		}
		tri.v0 = m_pVertexData->GetPositionDataAt(nTriIndex * 3 + 0);
		tri.v1 = m_pVertexData->GetPositionDataAt(nTriIndex * 3 + 1);
		tri.v2 = m_pVertexData->GetPositionDataAt(nTriIndex * 3 + 2);
	}
	else
	{
		if (m_pIndexData->indexNum < nTriIndex * 3)
		{
			return tri;
		}
		for (int i = 0; i < 3; ++i)
		{
			int nIndex = m_pIndexData->GetIndexAt(nTriIndex, i);
			if (nIndex >= m_pVertexData->nNumVertex)
			{
				return tri;
			}
			if (i == 0)
			{
				tri.v0 = m_pVertexData->GetPositionDataAt(nIndex);
			}
			else if (i == 1)
			{
				tri.v1 = m_pVertexData->GetPositionDataAt(nIndex);
			}
			else if (i == 2)
			{
				tri.v2 = m_pVertexData->GetPositionDataAt(nIndex);
			}		
		}
	}
	return tri;
}

ZG::Triangle ZG::IRenderable::GetWorldTriangle(int nIndex) const
{
	Triangle tri = GetTriangle(nIndex);
	if (m_pOwnerObj != nullptr)
	{
		Matrix44 mat = m_pOwnerObj->m_pTransform->GetWorldMatrix();
		Vector4 v;
		v.Vector3ToPoint(tri.v0);
		v = v * mat;
		tri.v0 = v;
		//
		v.Vector3ToPoint(tri.v1);
		v = v * mat;
		tri.v1 = v;
		//
		v.Vector3ToPoint(tri.v2);
		v = v * mat;
		tri.v2 = v;
	}
	return tri;
}

int ZG::IRenderable::GetTriangleNum() const
{
	if (m_pVertexData == nullptr)
	{
		return 0;
	}
	if (m_pIndexData == nullptr)
	{
		return m_pVertexData->nNumVertex / 3;
	}
	return m_pIndexData->indexNum / 3;
}
