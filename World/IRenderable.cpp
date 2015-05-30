#include "stdafx.h"
#include "IRenderable.h"
#include "CommonDef.h"
#include "BoundingBase.h"
#include "AABBBox.h"
#include "ResourceManager.h"
#include "MaterialResource.h"


IRenderable::IRenderable()
	:m_pVertexData(nullptr)
	, m_pIndexData(nullptr)
	, m_pSharedMaterial(nullptr)
	, m_pBounding(nullptr)
{
	
}


IRenderable::~IRenderable()
{
}

void IRenderable::Update()
{

}

shared_ptr<MaterialResource> IRenderable::GetDefaultMaterial()
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
		m_pVertexData->getBoundingMaxAndMin(vecMin, vecMax);
		AABBBox* m_pBox = new AABBBox();
		m_pBox->m_pMax = vecMax;
		m_pBox->m_pMin = vecMin;
	}
}
