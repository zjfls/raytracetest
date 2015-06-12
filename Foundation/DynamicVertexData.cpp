#include "stdafx.h"
#include "DynamicVertexData.h"
#include "MathDefine.h"
#include "AABBBox.h"
DynamicVertexData::DynamicVertexData()
{
}


DynamicVertexData::~DynamicVertexData()
{
}

void DynamicVertexData::getBoundingMaxAndMin(Vector3& min, Vector3& max)
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

	min.m_fx = min.m_fy = min.m_fz = MAXFLOAT;
	max.m_fx = max.m_fy = max.m_fz = MINFLOAT;
	//unsigned int nSize = m_PositionData.size();
	for each (Vector3 vPos in m_PositionData)
	{
		if (vPos.m_fx < min.m_fx)
		{
			min.m_fx = vPos.m_fx;
		}
		if (vPos.m_fy < min.m_fy)
		{
			min.m_fy = vPos.m_fy;
		}
		if (vPos.m_fz < min.m_fz)
		{
			min.m_fz = vPos.m_fz;
		}
		//
		if (vPos.m_fx > max.m_fx)
		{
			max.m_fx = vPos.m_fx;
		}
		if (vPos.m_fy > max.m_fy)
		{
			max.m_fy = vPos.m_fy;
		}
		if (vPos.m_fz > max.m_fz)
		{
			max.m_fz = vPos.m_fz;
		}

	}
	m_pAABB->m_Min = min;
	m_pAABB->m_Max = max;
}

void DynamicVertexData::autoGenDesc()
{
	if (m_PositionData.size() > 0)
	{
		VertexData::VertexDataDesc desc;
		desc.nOffset = 0;
		desc.typedesc = EVertexTypeFloat3;
		desc.usedesc = EVertexPosition;
		vecDataDesc.push_back(desc);
	}
}

ZG::Vector3 ZG::DynamicVertexData::GetPositionDataAt(int nIndex) const
{
	Vector3 pos;
	if (nIndex < m_PositionData.size())
	{
		pos = m_PositionData[nIndex];
	}
	return pos;
}
