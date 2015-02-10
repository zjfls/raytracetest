#pragma once
#include "Vector3.h"
class Ray3D
{
public:
	Ray3D();
	Ray3D(Point3D pos, Direction3D dir);
	virtual ~Ray3D();

//////////////////////////////////////////////////////
//
	Point3D m_vecPos;
	Direction3D m_vecDirection;
};

