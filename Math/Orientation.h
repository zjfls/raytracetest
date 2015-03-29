#pragma once
#include "Matrix33.h"
#include "Vector3.h"
class MATH_API Orientation
{
public:
	Orientation();
	virtual ~Orientation();
	Matrix33 ToMatrix33() const;
//////////////////////////////////////////////////
	Vector3 m_vecEulerAngle;


	
};

