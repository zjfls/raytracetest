#include "stdafx.h"
#include "Vector3.h"


Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z)
{
	m_fx = x;
	m_fy = y;
	m_fz = z;
}

Vector3::Vector3(const Vector3& in)
{
	m_fx = in.m_fx;
	m_fy = in.m_fy;
	m_fz = in.m_fz;
}


Vector3::~Vector3()
{
}

Vector3 Vector3::operator=(const Vector3& vecIn)
{
	m_fx = vecIn.m_fx;
	m_fy = vecIn.m_fy;
	m_fz = vecIn.m_fz;
	return *this;
}
