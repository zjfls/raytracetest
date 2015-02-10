#pragma once
#include "Orientation.h"

/////////////////////////////////////////////////
class Transform
{
public:
	Transform();
	~Transform();
////////////////////////////////////////////////
	Point3D m_vecTranslate;
	Orientation m_Orientation;
	Vector3 m_vecScale;
};

