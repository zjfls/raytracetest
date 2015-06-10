#pragma once
#include "BoundingBase.h"
#include "Vector3.h"
namespace ZG
{
	class Matrix44;
	class MATH_API AABBBox :
		public BoundingBase
	{
	public:
		AABBBox();
		virtual ~AABBBox();

		virtual bool testAABB(const AABBBox& aabb);
		virtual bool testRay(const Ray3D& r);



		void	Transform(Matrix44& mat);
		Vector3 m_Max;
		Vector3 m_Min;
	};

}

