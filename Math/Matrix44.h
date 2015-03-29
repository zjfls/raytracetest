#pragma once
class Matrix33;
class MATH_API Matrix44
{
public:
	Matrix44();
	Matrix44(const Matrix44& matIn);
	Matrix44(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9,float f10,float f11,float f12,float f13,float f14,float f15,float f16);
	Matrix44 operator=(const Matrix44& matIn);
	Matrix44 operator*(const Matrix44& matIn) const;
	Matrix44 Transpose() const;
	Matrix44 Inverse() const;
	virtual ~Matrix44();


	void TraslateMatrix(float fx,float fy,float fz);
	void FromMatrix33(const Matrix33* mat33);


	float M[4][4];
	static const Matrix44 Identity;
};

