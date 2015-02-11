#pragma once
class Sphere3D:public IRenderable
{
public:
	Sphere3D();
	Sphere3D(Point3D, float fRadius);
	virtual ~Sphere3D();

////////////////////////////////////////////////
	float m_fRadius;
};

