#include "stdafx.h"
#include "AABBBox.h"
#include <vector>
#include "Vector4.h"
AABBBox::AABBBox()
{
}


AABBBox::~AABBBox()
{
}

bool AABBBox::testAABB(const AABBBox& aabb)
{
	return true;
}

bool AABBBox::testRay(const Ray3D& r)
{
	return true;
}

void AABBBox::Transform(Matrix44& mat)
{
	std::vector<Vector3> ptList;
	ptList.push_back(m_Min);
	ptList.push_back(m_Max);
	ptList.push_back(Vector3(m_Min.m_fx, m_Min.m_fy, m_Max.m_fz));
	ptList.push_back(Vector3(m_Min.m_fx, m_Max.m_fy, m_Max.m_fz));
	ptList.push_back(Vector3(m_Min.m_fx, m_Max.m_fy, m_Min.m_fz));

	ptList.push_back(Vector3(m_Max.m_fx, m_Max.m_fy, m_Min.m_fz));
	ptList.push_back(Vector3(m_Max.m_fx, m_Min.m_fy, m_Max.m_fz));
	ptList.push_back(Vector3(m_Max.m_fx, m_Min.m_fy, m_Min.m_fz));

	
	Vector4 min, max;
	min.Vector3ToPoint(m_Min);
	max.Vector3ToPoint(m_Max);
	min = min * mat;
	max = max * mat;
	if (min.m_fw != 0.0f)
	{
		min = min * fabs(1.0f / min.m_fw);
	}
	if (max.m_fw != 0.0f)
	{
		max = max * fabs(1.0f / max.m_fw);
	}
	for each (Vector3 v in ptList)
	{
		Vector4 vPos;
		vPos.Vector3ToPoint(v);
		vPos = vPos * mat;
		if (vPos.m_fw != 0.0f)
		{
			vPos = vPos * fabs(1.0f / vPos.m_fw);
		}
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
	m_Min = min;
	m_Max = max;
}
