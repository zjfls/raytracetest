#pragma once
#include "IRenderable.h"
class Plane3D:public IRenderable
{
public:
	//Plane3D();
	Plane3D(const Point3D& vecPt,const Direction3D& vecNormal);
	virtual ~Plane3D();

	Point3D m_vecPt;
	Direction3D m_vecNormal;
private:
	Plane3D();
	friend class IWorldObj;
};


