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
	struct stRayTestOption
	{
		stRayTestOption(){ bTestBackFace = false; };
		bool bTestBackFace;
		bool bSort;
		int  nSortType;//0����Զ��1Զ����
	};
	class MAIN_API IntersectTest
	{
	public:
		IntersectTest();
		virtual ~IntersectTest();

		static IntersectResults testRayRenderables(const Ray3D& r, SmartPointer<IRenderable> renderable, Transform& trans);
		static IntersectResults testRaySphere(const Ray3D& r, const Sphere3D& s, const Transform& trans);
		static IntersectResults testRayPlane(const Ray3D& r, const Plane3D& p, const Transform& trans);
		static IntersectResults testRayMesh(const Ray3D& r, const Mesh& mesh, const Transform& trans);

		//
		static bool AABBBox_AABBBoxTest(const AABBBox& a, const AABBBox& b);
	private:
		static IntersectResults testRayTriangle(const Ray3D& r, const Triangle& tri);
		static bool SortByDistance(const IntersectData& d1, const IntersectData& d2);
	};

}