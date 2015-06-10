#pragma once
/******************************************************
//Bounding Box
*******************************************************/
namespace ZG
{
	class AABBBox;
	class Ray3D;
	class MATH_API BoundingBase
	{
	public:
		BoundingBase();
		virtual ~BoundingBase();


		virtual bool testAABB(const AABBBox& aabb) = 0;
		virtual bool testRay(const Ray3D& r) = 0;
	};
}
