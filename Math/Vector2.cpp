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
