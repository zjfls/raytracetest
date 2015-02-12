#include "stdafx.h"
#include "Orientation.h"


Orientation::Orientation()
{
}


Orientation::~Orientation()
{
}

Matrix33 Orientation::ToMatrix33() const
{
	Matrix33 matX, matY, matZ;
	matX.RotAboutX(m_vecEulerAngle.m_fx);
	matY.RotAboutY(m_vecEulerAngle.m_fy);
	matZ.RotAboutZ(m_vecEulerAngle.m_fz);

	return matX * matY * matZ;
}
