#pragma once
#include "IntersetResults.h"
class Ray3D;
class Sphere3D;
class Plane3D;
class Mesh;
class Triangle;
struct stRayTestOption
{
	stRayTestOption(){ bTestBackFace = false; };
	bool bTestBackFace;
	bool bSort;
	int  nSortType;//0近到远，1远到近
};
class IntersectTest
{
public:
	IntersectTest();
	virtual ~IntersectTest();

	static IntersectResults testRayRenderables(const Ray3D& r, IRenderable* renderable, Transform& trans);
	static IntersectResults testRaySphere(const Ray3D& r, const Sphere3D& s, const Transform& trans);
	static IntersectResults testRayPlane(const Ray3D& r, const Plane3D& p, const Transform& trans);


	static IntersectResults testRayMesh(const Ray3D& r, const Mesh& mesh, const Transform& trans);
private:
	static IntersectResults testRayTriangle(const Ray3D& r,const Triangle);
	static bool SortByDistance(const IntersectData& d1, const IntersectData& d2);
};

