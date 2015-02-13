#pragma once
#include "IntersetResults.h"
class Ray3D;
class Sphere3D;
class IntersectTest
{
public:
	IntersectTest();
	virtual ~IntersectTest();

	static IntersetResults testRayRenderables(const Ray3D& r, IRenderable* renderable, Transform& trans);
	static IntersetResults testRaySphere(const Ray3D& r, const Sphere3D& s, const Transform& trans);
};

