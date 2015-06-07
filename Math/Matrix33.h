#pragma once
#include "Vector3.h"
class Matrix44;
class Vector3;
class MATH_API Matrix33
{
public:
	Matrix33();
	virtual ~Matrix33();
	Matrix33(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9);
	Matrix33(const Matrix33& matIn);
	Matrix33	operator=(const Matrix33& matIn);
	Matrix33	operator*(const Matrix33& matIn);
	Matrix33	Transpose() const;
	Matrix33	Inverse() const;
	Vector3		GetForwardDir() const;
	float		Determinate() const;
	bool	IsOrthogonal() const;
	void RotAboutX(float f);
	void RotAboutY(float f);
	void RotAboutZ(float f);
	void RotAboutVector(const Vector3& vec,float f);
	void ScaleMatrix(float fX,float fY,float fZ);
	void FromMatrix44(const Matrix44* mat44);
	void FromEulerAngleYXZ(const Vector3& v);
	Vector3 toEulerAngleYXZ();

	
	//static Vector3  operator*(Vector3& v, Matrix33& mat);
	//void ScaleY(float f);
	//void ScaleZ(float f);
	const static Matrix33 Identity;



	float M[3][3];
};

