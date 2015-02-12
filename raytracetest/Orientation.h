#pragma once
#include "Matrix33.h"
class Orientation
{
public:
	Orientation();
	virtual ~Orientation();
	Matrix33 ToMatrix33() const;
//////////////////////////////////////////////////
	Vector3 m_vecEulerAngle;


	
};

