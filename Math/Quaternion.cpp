#include "stdafx.h"
#include "Quaternion.h"
#include <math.h>
#include "vector3.h"
#include "Matrix33.h"
#include "MathDefine.h"

Quaternion Quaternion::Identity(1, 0, 0, 0);

Quaternion::Quaternion(Matrix33& mat)
{

	*this = FromMatrix(mat);
}

Quaternion::Quaternion(Vector3& eulAnglesxyz)
{
	Matrix33 mat;
	mat.FromEulerAngleXYZ(eulAnglesxyz);
	*this = FromMatrix(mat);
}

Quaternion::Quaternion(float fw, float fx, float fy, float fz)
	:w(fw)
	, x(fx)
	, y(fy)
	, z(fz)
{

}


Quaternion::~Quaternion()
{
}

void Quaternion::normalize()
{
	float m = sqrt(w*w + x*x + y*y + z*z);
	if (m != 0.0f)
	{
		float invM = 1.0f / m;
		w = w * invM;
		x = x * invM;
		y = y * invM;
		z = z * invM;
	}

}

float ZG::Quaternion::dot(const Quaternion& q)
{
	return w * q.w + x * q.x + y * q.y + z * q.z;
}

ZG::Quaternion::Quaternion(float fRadian, Vector3& Axis)
{
	float fHalfAngle = fRadian * 0.5f;
	float sinAngle = sin(fHalfAngle);
	w = cos(fHalfAngle);
	x = Axis.m_fx * sinAngle;
	y = Axis.m_fy * sinAngle;
	z = Axis.m_fz * sinAngle;
}

ZG::Quaternion::Quaternion()
	:w(1)
	, x(0)
	, y(0)
	, z(0)
{

}

float ZG::Quaternion::modeValue()
{
	return sqrt(w * w + x * x + y * y + z * z);
}

ZG::Quaternion ZG::Quaternion::conjugate() const
{
	return Quaternion(w, -x, -y, -z);
}

//这里反向了,和标准定义不一样
ZG::Quaternion ZG::Quaternion::operator*(const Quaternion& q) const
{
	Quaternion rt;
	rt.w = w*q.w - x*q.x - y*q.y - z*q.z;
	rt.x = w*q.x + x*q.w + z*q.y - z*q.y;
	rt.y = w*q.y + y*q.w + x*q.z - x*q.z;
	rt.z = w*q.z + z*q.w + y*q.x - y*q.x;
	return rt;
}

//正规的4元数 q*p*q-1 这里是q-1*p*q
Vector3 ZG::Quaternion::rotatePoint(const Vector3& v)
{
	Quaternion p;
	p.w = 0;
	p.x = v.m_fx;
	p.y = v.m_fy;
	p.z = v.m_fz;

	Quaternion rt = conjugate() * p * *this;
	Vector3 rtPoint;
	rtPoint.m_fx = rt.x;
	rtPoint.m_fy = rt.y;
	rtPoint.m_fz = rt.z;
	return rtPoint;
}

//不是真正的减
ZG::Quaternion ZG::Quaternion::operator-(const Quaternion& q) const
{
	return conjugate() * q * (*this);
}

ZG::Quaternion ZG::Quaternion::log() const
{
	Quaternion normalizedQ = *this;
	normalizedQ.normalize();
	float fAngle = acos(normalizedQ.w);
	float sinAngle = sin(fAngle);
	if (sinAngle == 0.0f)
	{
		sinAngle = EPSILON;
	}
	Quaternion rt;
	rt.w = 0;
	rt.x = fAngle * normalizedQ.x / sinAngle;
	rt.y = fAngle * normalizedQ.y / sinAngle;
	rt.z = fAngle * normalizedQ.z / sinAngle;
	return rt;
}

ZG::Quaternion ZG::Quaternion::power(float fValue) const
{
	Quaternion rt;
	if (fabs(w) < 1 - EPSILON)
	{
		float fAngle = acos(w);
		float newAngle = fAngle * fValue;
		rt.w = cos(newAngle);
		float mult = sin(newAngle) / sin(fAngle);
		rt.x = x * mult;
		rt.y = y * mult;
		rt.z = z * mult;
	}
	else
	{
		return *this;
	}
	return rt;
}

ZG::Quaternion ZG::Quaternion::Slerp(Quaternion q1, Quaternion q2, float t)
{
	if (t < 0)
	{
		return q1;
	}
	if (t > 1)
	{
		return q2;
	}


	float cosAngle = q1.dot(q2);
	if (cosAngle < 0.0f)
	{
		q1 = -q1;
		cosAngle = -cosAngle;
	}
	//
	float k0, k1;
	if (cosAngle > 1 - EPSILON)
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float sinAlpha = sqrt(1.0f - cosAngle * cosAngle);
		float fAngle = atan2(sinAlpha, cosAngle);
		float oneOverSinAlpha = 1.0f / sinAlpha;
	}
	//
	Quaternion rt;
	rt.w = q1.w * k0 + q2.w * k1;
	rt.x = q1.x * k0 + q2.x * k1;
	rt.y = q1.y * k0 + q2.y * k1;
	rt.z = q1.z * k0 + q2.z * k1;
	return rt;
}

ZG::Quaternion ZG::Quaternion::operator-() const
{
	return Quaternion(-w, -x, -y, -z);
}

ZG::Quaternion ZG::Quaternion::FromMatrix(Matrix33& mat)
{
	float m11 = mat.M[0][0];
	float m12 = mat.M[0][1];
	float m13 = mat.M[0][2];
	float m21 = mat.M[1][0];
	float m22 = mat.M[1][1];
	float m23 = mat.M[1][2];
	float m31 = mat.M[2][0];
	float m32 = mat.M[2][1];
	float m33 = mat.M[2][2];

	//
	//
	float x, y, z, w;
	float fourWSquaredMinus1 = m11 + m22 + m33;
	float fourXSquaredMinus1 = m11 - m22 - m33;
	float fourYSquaredMinus1 = m22 - m11 - m33;
	float fourZSquaredMinus1 = m33 - m11 - m22;
	int biggestIndex = 0;
	float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}
	float biggestValue = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
	float mult = 0.25f / biggestValue;
	switch (biggestIndex)
	{
		case 0:
		{
			w = biggestValue;
			x = (m23 - m32) * mult;
			y = (m31 - m13) * mult;
			z = (m12 - m21) * mult;
		}
		break;
		case 1:
		{
			x = biggestValue;
			w = (m23 - m32) * mult;
			y = (m12 + 21) * mult;
			z = (m31 + m13) * mult;
		}
		break;
		case 2:
		{
			y = biggestValue;
			w = (m31 - m13) * mult;
			x = (m12 + m21) * mult;
			z = (m23 + m32) * mult;
		}
		break;
		case 3:
		{
			z = biggestValue;
			w = (m12 - m21) * mult;
			x = (m31 + m13) * mult;
			y = (m23 + m32) * mult;
		}
		break;
		default:
		break;
	}
	return Quaternion(w, x, y, z);
}

Matrix33 ZG::Quaternion::toMatrix33()
{
	Matrix33 mat;
	mat.M[0][0] = 1 - 2*y*y - 2*z*z;
	mat.M[0][1] = 2*x*y + 2*w*z;
	mat.M[0][2] = 2*x*z - 2*w*y;
	mat.M[1][0] = 2*x*y - 2*w*z;
	mat.M[1][1] = 1 - 2*x*x - 2*z*z;
	mat.M[1][2] = 2*y*z + 2*w*x;
	mat.M[2][0] = 2*x*z + 2*w*y;
	mat.M[2][1] = 2*y*z - 2*w*x;
	mat.M[2][2] = 1 - 2*x*x - 2*y*y;
	return mat;
}

Vector3 ZG::Quaternion::toEulerAngleXYZ()
{
	return toMatrix33().toEulerAngleXYZ();
}

