#include "stdafx.h"
#include "Matrix33.h"
#include "Matrix44.h"
const Matrix33 Matrix33::Identity = Matrix33(1,0,0,0,1,0,0,0,1);

Matrix33::Matrix33()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			M[i][j] = 0.0f;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		M[i][i] = 1.0f;
	}
}

Matrix33::Matrix33(const Matrix33& matIn)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			M[i][j] = matIn.M[i][j];
		}
	}
}

Matrix33::Matrix33(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9)
{
	M[0][0] = f1;
	M[0][1] = f2;
	M[0][2] = f3;
	M[1][0] = f4;
	M[1][1] = f5;
	M[1][2] = f6;
	M[2][0] = f7;
	M[2][1] = f8;
	M[2][2] = f9;
}


Matrix33::~Matrix33()
{
}

Matrix33 Matrix33::operator=(const Matrix33& matIn)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			M[i][j] = matIn.M[i][j];
		}
	}
	return *this;
}

Matrix33 Matrix33::operator*(const Matrix33& matIn)
{
	Matrix33 matRet;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matRet.M[i][j] = 0.0f;
			for (int ii = 0; ii < 3; ++ii)
			{
				matRet.M[i][j] += M[i][ii] * matIn.M[ii][j];
			}
		}
	}
	return matRet;
}

void Matrix33::RotAboutX(float f)
{
	float cosf = cos(f);
	float sinf = sin(f);
	*this = Identity;
	M[1][1] = cosf;
	M[1][2] = sinf;
	M[2][1] = -sinf;
	M[2][2] = cosf;
}




void Matrix33::RotAboutY(float f)
{
	float cosf = cos(f);
	float sinf = sin(f);
	*this = Identity;
	M[0][0] = cosf;
	M[0][2] = -sinf;
	M[2][0] = sinf;
	M[2][2] = cosf;
}


void Matrix33::RotAboutZ(float f)
{
	float cosf = cos(f);
	float sinf = sin(f);
	*this = Identity;
	M[0][0] = cosf;
	M[0][1] = sinf;
	M[1][0] = -sinf;
	M[1][1] = cosf;
}




void Matrix33::RotAboutVector(Vector3 vec,float f)
{
	vec.normalize();
	float cosf = cos(f);
	float sinf = sin(f);
	*this = Identity;
	M[0][0] = cosf + (1 - cosf) * vec.m_fx * vec.m_fx;
	M[0][1] = (1 - cosf) * vec.m_fx * vec.m_fy - sinf * vec.m_fz;
	M[0][2] = (1 - cosf)* vec.m_fx * vec.m_fz + sinf * vec.m_fy;
	M[1][0] = (1 - cosf) * vec.m_fy * vec.m_fx + sinf * vec.m_fz;
	M[1][1] = cosf + (1 - cosf) * vec.m_fy * vec.m_fy;
	M[1][2] = (1 - cosf) * vec.m_fy * vec.m_fz - sinf * vec.m_fx;
	M[2][0] = (1 - cosf) * vec.m_fz * vec.m_fx - sinf * vec.m_fy;
	M[2][1] = (1 - cosf) * vec.m_fy * vec.m_fz + sinf * vec.m_fx;
	M[2][2] = cosf + (1 - cosf) * vec.m_fz * vec.m_fz;
}

void Matrix33::ScaleMatrix(float fX, float fY, float fZ)
{
	*this = Identity;
	M[0][0] = fX;
	M[1][1] = fY;
	M[2][2] = fZ;
}

void Matrix33::FromMatrix44(const Matrix44* mat44)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			M[i][j] = mat44->M[i][j];
		}
	}
}

Matrix33 Matrix33::Transpose() const
{
	Matrix33 matRet;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matRet.M[i][j] = M[j][i];
		}
	}
	return matRet;
}

Matrix33 Matrix33::Inverse() const
{
	Matrix33 matRet;
	return matRet;
}
