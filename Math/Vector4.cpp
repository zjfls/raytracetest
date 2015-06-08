#include "stdafx.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix44.h"

Vector4::Vector4()
{
	m_fx = 0.0f;
	m_fy = 0.0f;
	m_fz = 0.0f;
	m_fw = 0.0f;
}


Vector4::~Vector4()
{
}

void Vector4::Vector3ToPoint(const Vector3& vec3In)
{
	m_fx = vec3In.m_fx;
	m_fy = vec3In.m_fy;
	m_fz = vec3In.m_fz;
	m_fw = 1.0f;
}

void Vector4::Vector3ToDirection(const Vector3& vec3In)
{
	m_fx = vec3In.m_fx;
	m_fy = vec3In.m_fy;
	m_fz = vec3In.m_fz;
	m_fw = 0.0f;
}

void Vector4::ToVector3(Vector3& vecIn) const
{
	float fw = m_fw;
	if (fw == 0)
	{
		fw = 1.0f;
	}
	vecIn.m_fx = m_fx / fw;
	vecIn.m_fy = m_fy / fw;
	vecIn.m_fz = m_fz / fw;
}

Vector4 Vector4::operator*(const Matrix44& mat44) const
{
	Vector4 vec4Ret;
	vec4Ret.m_fx = m_fx * mat44.M[0][0] + m_fy * mat44.M[1][0] + m_fz * mat44.M[2][0] + m_fw * mat44.M[3][0];
	vec4Ret.m_fy = m_fx * mat44.M[0][1] + m_fy * mat44.M[1][1] + m_fz * mat44.M[2][1] + m_fw * mat44.M[3][1];
	vec4Ret.m_fz = m_fx * mat44.M[0][2] + m_fy * mat44.M[1][2] + m_fz * mat44.M[2][2] + m_fw * mat44.M[3][2];
	vec4Ret.m_fw = m_fx * mat44.M[0][3] + m_fy * mat44.M[1][3] + m_fz * mat44.M[2][3] + m_fw * mat44.M[3][3];
	//if (vec4Ret.m_fw != 0.0f)
	//{
	//	float fratio = 1 / vec4Ret.m_fw;
	//	vec4Ret = vec4Ret * fratio;
	//}
	return vec4Ret;
}

Vector4 Vector4::operator*(float f) const
{
	Vector4 vec4Ret;
	vec4Ret.m_fx = m_fx * f;
	vec4Ret.m_fy = m_fy * f;
	vec4Ret.m_fz = m_fz * f;
	vec4Ret.m_fw = m_fw * f;
	return vec4Ret;
}
