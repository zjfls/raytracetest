#pragma once
#include "Orientation.h"
#include "ModuleBase.h"

/////////////////////////////////////////////////
class Transform:public ModuleBase
{
public:
	Transform();
	~Transform();
////////////////////////////////////////////////
	Point3D m_vecTranslate;
	Orientation m_Orientation;
	Vector3 m_vecScale;
};

