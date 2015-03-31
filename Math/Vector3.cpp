#include "stdafx.h"
#include "Vector3.h"
const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ONE = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::XAxis = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::YAxis = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ZAxis = Vector3(0.0f, 0.0f, 1.0f);

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

void Vector3::normalize()
{
	float fLength = length();
	if (fLength == 0.0f)
	{
		return;
	}
	*this = *this * (1.0f / fLength);
}

float Vector3::length() const
{
	return sqrt(m_fx * m_fx + m_fy * m_fy + m_fz * m_fz);
}

Vector3 Vector3::operator*(float f) const
{
	Vector3 vecRt;
	vecRt.m_fx = m_fx * f;
	vecRt.m_fy = m_fy * f;
	vecRt.m_fz = m_fz * f;


	return vecRt;
}

Vector3 Vector3::operator-() const
{
	//Vector3 vecRt;
	return *this * -1;
}

Vector3 Vector3::operator-(const Vector3& vecIn) const
{
	return *this + -1 * vecIn;
}

Vector3 Vector3::operator+(const Vector3& vecIn) const
{
	Vector3 vecRt;
	vecRt.m_fx = m_fx + vecIn.m_fx;
	vecRt.m_fy = m_fy + vecIn.m_fy;
	vecRt.m_fz = m_fz + vecIn.m_fz;
	return vecRt;
}

float Vector3::distance(const Vector3& vecTarget) const
{
	Vector3 vecDiff = vecTarget - *this;
	return vecDiff.length();
}

float Vector3::dot(const Vector3& vecIn) const
{
	float fDot = m_fx * vecIn.m_fx + m_fy * vecIn.m_fy + m_fz * vecIn.m_fz;
	return fDot;
}

Vector3 Vector3::cross(const Vector3& vecIn) const
{
	Vector3 vecOut;
	vecOut.m_fx = m_fy * vecIn.m_fz - m_fz * vecIn.m_fy;
	vecOut.m_fy = m_fz * vecIn.m_fx - m_fx * vecIn.m_fz;
	vecOut.m_fz = m_fx * vecIn.m_fy - m_fy * vecIn.m_fx;
	return vecOut;
}