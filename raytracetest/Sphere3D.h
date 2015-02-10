#pragma once
class Sphere3D
{
public:
	Sphere3D();
	Sphere3D(Point3D ptCenter, float fRadius);
	virtual ~Sphere3D();

////////////////////////////////////////////////
	Point3D m_fCenter;
	float m_fRadius;
};

