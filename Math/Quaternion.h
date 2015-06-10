#pragma once
#include "Matrix33.h"
#include "Vector3.h"


namespace ZG
{
	class Matrix33;
	class Orientation;
	class Vector3;
	class MATH_API Quaternion
	{
	public:
		Quaternion();
		virtual ~Quaternion();
		Quaternion(Matrix33& mat);
		//Quaternions(Orientation& ori);
		Quaternion(Vector3& eulAnglesyxz);
		Quaternion(float fw, float fx, float fy, float fz);
		Quaternion(float fRadian, Vector3& Axis);
		//
		Vector3		toEulerAngleYXZ();
		Matrix33	toMatrix33();
		//
		void	normalize();
		float	modeValue();
		float	dot(const Quaternion& q);
		Quaternion	conjugate() const;
		//同矩阵，满足结合率，不满足交换率
		Quaternion	operator*(const Quaternion& q) const;
		Quaternion	operator-(const Quaternion& q) const;
		Quaternion  operator-() const;
		Quaternion	log() const;
		Quaternion	power(float fValue) const;
		//
		Vector3	rotatePoint(const Vector3& v);
		static Quaternion Slerp(Quaternion q1, Quaternion q2, float t);
		static Quaternion	FromMatrix(Matrix33& mat);

		//
	public:
		float w, x, y, z;
		static Quaternion Identity;
	};

}

