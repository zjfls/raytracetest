#pragma once
#include "IntersetResults.h"
namespace ZG
{
	class Ray3D;
	class Sphere3D;
	class Plane3D;
	class Mesh;
	class Triangle;
	class Transform;
	class AABBBox;
	class BoundingBase;
	class IRenderable;
	struct stRayTestOption
	{
		stRayTestOption(){ bTestBackFace = false; };
		bool bTestBackFace;
		bool bSort;
		int  nSortType;//0近到远，1远到近
	};
	class MAIN_API IntersectTest
	{
	public:
		IntersectTest();
		virtual ~IntersectTest();

		static IntersectResults testRayRenderables(const Ray3D& r, SmartPointer<IRenderable> renderable, Transform& trans);
		static IntersectResults testRaySphere(const Ray3D& r, const Sphere3D& s, const Transform& trans);
		static IntersectResults testRayPlane(const Ray3D& r, const Plane3D& p, const Transform& trans);
		static IntersectResults testRayRenderable(const Ray3D& r, const IRenderable& mesh, const Transform& trans);


		static bool Ray_BoundingTest(const Ray3D& r, const BoundingBase& b, float t0, float t1);
		//
		static bool Ray_AABBBoxTest(const Ray3D& r, const AABBBox& b, float t0, float t1);
		static bool AABBBox_AABBBoxTest(const AABBBox& a, const AABBBox& b);
	private:
		static IntersectResults testRayTriangle(const Ray3D& r, const Triangle& tri);
		static bool SortByDistance(const IntersectData& d1, const IntersectData& d2);
	};

}