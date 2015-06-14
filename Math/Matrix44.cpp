#include "stdafx.h"
#include "Matrix44.h"
#include "Matrix33.h"
const Matrix44 Matrix44::Identity = Matrix44(1, 0, 0, 0,
0, 1, 0, 0,
0, 0, 1, 0,
0, 0, 0, 1 );



Matrix44::Matrix44()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			M[i][j] = 0.0f;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		M[i][i] = 1.0f;
	}
}

Matrix44::Matrix44(const Matrix44& matIn)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			M[i][j] = matIn.M[i][j];
		}
	}
}

Matrix44::Matrix44(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15, float f16)
{
	M[0][0] = f1;
	M[0][1] = f2;
	M[0][2] = f3;
	M[0][3] = f4;
	M[1][0] = f5;
	M[1][1] = f6;
	M[1][2] = f7;
	M[1][3] = f8;
	M[2][0] = f9;
	M[2][1] = f10;
	M[2][2] = f11;
	M[2][3] = f12;
	M[3][0] = f13;
	M[3][1] = f14;
	M[3][2] = f15;
	M[3][3] = f16;
}


Matrix44::~Matrix44()
{
}

Matrix44 Matrix44::operator=(const Matrix44& matIn)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			M[i][j] = matIn.M[i][j];
		}
	}
	return *this;
}

Matrix44 Matrix44::operator*(const Matrix44& matIn) const
{
	Matrix44 matRet;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			matRet.M[i][j] = 0.0f;
			for (int ii = 0; ii < 4; ++ii)
			{
				matRet.M[i][j] += M[i][ii] * matIn.M[ii][j];
			}
		}
	}
	return matRet;
}

void Matrix44::FromMatrix33(const Matrix33* mat33)
{
	*this = Identity;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			M[i][j] = mat33->M[i][j];
		}
	}
}

void Matrix44::TraslateMatrix(float fx, float fy, float fz)
{
	*this = Identity;
	M[3][0] = fx;
	M[3][1] = fy;
	M[3][2] = fz;
	//m_Matrix[3][3] = 1.0f;
}

Matrix44 Matrix44::Transpose() const
{
	Matrix44 matRet;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			matRet.M[i][j] = M[j][i];
		}
	}
	return matRet;
}

Matrix44 Matrix44::Inverse() const
{
	Matrix44 matRet;
	return matRet;
}

Matrix44 Matrix44::QuikInverse(const Matrix44& mat)
{
	Vector3 translate = mat.GetTranslate();
	Vector3 scale = mat.GetScale();
	Vector3 invScale = Vector3(1 / scale.m_fx, 1 / scale.m_fy, 1 / scale.m_fz);
	Matrix33 mat33;
	mat33.FromMatrix44(&mat);
	for (int i = 0; i < 3; ++i)
	{
		mat33.M[0][i] /= scale.m_fx;
		mat33.M[1][i] /= scale.m_fy;
		mat33.M[2][i] /= scale.m_fz;
	}
	Matrix33 mat33RotInv = mat33.Transpose();

	Matrix44 si, ri, ti;
	ti = Matrix44::GetTranlateMatrix(-translate);
	si = Matrix44::GetScaleMatrix(invScale);
	ri.FromMatrix33(&mat33RotInv);



	return ti * ri * si;
	
	
}

Vector3 Matrix44::GetTranslate() const
{
	Vector3 vecRt;
	vecRt.m_fx = M[3][0];
	vecRt.m_fy = M[3][1];
	vecRt.m_fz = M[3][2];
	return vecRt;
}

Vector3 Matrix44::GetScale() const
{
	Vector3 vecRt,vec1,vec2,vec3;
	vec1 = Vector3(M[0][0], M[0][1], M[0][2]);
	vec2 = Vector3(M[1][0], M[1][1], M[1][2]);
	vec3 = Vector3(M[2][0], M[2][1], M[2][2]);
	vecRt.m_fx = vec1.length();
	vecRt.m_fy = vec2.length();
	vecRt.m_fz = vec3.length();
	return vecRt;
}

Vector3 Matrix44::GetRotation() const
{
	Vector3 vecRt, vec1, vec2, vec3;
	vec1 = Vector3(M[0][0], M[0][1], M[0][2]);
	vec2 = Vector3(M[1][0], M[1][1], M[1][2]);
	vec3 = Vector3(M[2][0], M[2][1], M[2][2]);
	vec1.normalize();
	vec2.normalize();
	vec3.normalize();
	float x, y, z;
	x = atan2(vec2.m_fz, vec3.m_fz);
	float cosy = sqrt(vec1.m_fx * vec1.m_fx + vec1.m_fy * vec1.m_fy);
	y = atan2(-vec1.m_fz, cosy);
	
	float sinx = sin(x);
	float cosx = cos(x);
	z = atan2(sinx * vec3.m_fx - cosx * vec2.m_fx, cosx * vec2.m_fy - sinx * vec3.m_fy);
	vecRt = Vector3(x, y, z);
	//to do
	return vecRt;
}

Matrix44 Matrix44::GetTranlateMatrix(const Vector3& translate)
{
	Matrix44 mat;
	mat.TraslateMatrix(translate.m_fx, translate.m_fy, translate.m_fz);
	return mat;
}

Matrix44 Matrix44::GetScaleMatrix(const Vector3& scale)
{
	Matrix44 mat;
	mat.ScaleMatrix(scale.m_fx, scale.m_fy, scale.m_fz);
	return mat;
}

void Matrix44::ScaleMatrix(float fx, float fy, float fz)
{
	*this = Identity;
	M[0][0] = fx;
	M[1][1] = fy;
	M[2][2] = fz;
}
