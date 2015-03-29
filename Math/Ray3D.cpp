#include "stdafx.h"
#include "Ray3D.h"


//Ray3D::Ray3D()
//{
//}


Ray3D::~Ray3D()
{
}

Ray3D::Ray3D(Point3D pos, Direction3D dir)
{
	m_vecDirection = dir;
	m_vecDirection.normalize();
	m_vecPos = pos;
}
