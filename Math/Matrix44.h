#pragma once
#include "Vector3.h"
namespace ZG
{
	class Matrix33;
	//scale,rotation,translate
	class MATH_API Matrix44
	{
	public:
		Matrix44();
		Matrix44(const Matrix44& matIn);
		Matrix44(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15, float f16);
		Matrix44 operator=(const Matrix44& matIn);
		Matrix44 operator*(const Matrix44& matIn) const;
		Matrix44 Transpose() const;
		Matrix44 Inverse() const;


		static Matrix44 FromVector(const Vector3& translate, const Vector3& rotation, const Vector3& scale);
		static Matrix44 GetRotationMatrix(const Vector3& rotation);
		static Matrix44 GetTranlateMatrix(const Vector3& translate);
		static Matrix44 GetScaleMatrix(const Vector3& scale);
		Vector3			TransformPosition(const Vector3& vecPos);
		Vector3			TransformDirection(const Vector3& vecDir);


		Vector3	GetTranslate() const;
		Vector3 GetScale() const;
		Vector3 GetRotation() const;
		//¼Ù¶¨3x3¾ØÕóÕý½»
		static Matrix44 QuikInverse(const Matrix44& mat);
		virtual ~Matrix44();


		void TraslateMatrix(float fx, float fy, float fz);
		void ScaleMatrix(float fx, float fy, float fz);
		void FromMatrix33(const Matrix33* mat33);


		float M[4][4];
		static const Matrix44 Identity;
	};

}