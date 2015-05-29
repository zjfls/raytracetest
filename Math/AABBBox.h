#pragma once
#include "BoundingBase.h"
#include "Vector3.h"
class MATH_API AABBBox :
	public BoundingBase
{
public:
	AABBBox();
	virtual ~AABBBox();

	virtual bool testAABB(const AABBBox& aabb);
	virtual bool testRay(const Ray3D& r);
	Vector3 m_pMax;
	Vector3 m_pMin;
};

