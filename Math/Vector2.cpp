#include "stdafx.h"
#include "Vector2.h"


Vector2::Vector2()
{
}


Vector2::~Vector2()
{
}

Vector2 Vector2::operator-(const Vector2& v)
{
	return Vector2(m_fx - v.m_fx, m_fy - v.m_fy);
}

void ZG::Vector2::normalize()
{
	if (m_fx == 0.0f && m_fy == 0.0f)
	{
		return;
	}

}

float ZG::Vector2::length()
{
	float fValue = m_fx * m_fx + m_fy * m_fy;
	return sqrt(fValue);
}
