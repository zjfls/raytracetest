#include "stdafx.h"
#include "Plane3D.h"


Plane3D::Plane3D()
{
}

ZG::Plane3D::Plane3D(const Point3D& vecPt, const Direction3D& vecNormal)
{
	m_vecPt = vecPt;
	m_vecNormal = vecNormal;
}


Plane3D::~Plane3D()
{
}

//Plane3DCreator::Plane3DCreator()
//{
//
//}
//
//Plane3DCreator::~Plane3DCreator()
//{
//
//}
//
//ModuleBase* Plane3DCreator::CreateModule()
//{
//	return new Plane3D;
//}
