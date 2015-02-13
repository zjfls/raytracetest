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
			m_Matrix[i][j] = 0.0f;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		m_Matrix[i][i] = 1.0f;
	}
}

Matrix33::Matrix33(const Matrix33& matIn)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_Matrix[i][j] = matIn.m_Matrix[i][j];
		}
	}
}

Matrix33::Matrix33(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9)
{
	m_Matrix[0][0] = f1;
	m_Matrix[0][1] = f2;
	m_Matrix[0][2] = f3;
	m_Matrix[1][0] = f4;
	m_Matrix[1][1] = f5;
	m_Matrix[1][2] = f6;
	m_Matrix[2][0] = f7;
	m_Matrix[2][1] = f8;
	m_Matrix[2][2] = f9;
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
			m_Matrix[i][j] = matIn.m_Matrix[i][j];
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
			matRet.m_Matrix[i][j] = 0.0f;
			for (int ii = 0; ii < 3; ++ii)
			{
				matRet.m_Matrix[i][j] += m_Matrix[i][ii] * matIn.m_Matrix[ii][j];
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
	m_Matrix[1][1] = cosf;
	m_Matrix[1][2] = sinf;
	m_Matrix[2][1] = -sinf;
	m_Matrix[2][2] = cosf;
}




void Matrix33::RotAboutY(float f)
{
	float cosf = cos(f);
	float sinf = sin(f);
	*this = Identity;
	m_Matrix[0][0] = cosf;
	m_Matrix[0][2] = -sinf;
	m_Matrix[2][0] = sinf;
	m_Matrix[2][2] = cosf;
}


void Matrix33::RotAboutZ(float f)
{
	float cosf = cos(f);
	float sinf = sin(f);
	*this = Identity;
	m_Matrix[0][0] = cosf;
	m_Matrix[0][1] = sinf;
	m_Matrix[1][0] = -sinf;
	m_Matrix[1][1] = cosf;
}




void Matrix33::RotAboutVector(Vector3 vec,float f)
{
	vec.normalize();
	float cosf = cos(f);
	float sinf = sin(f);
	*this = Identity;
	m_Matrix[0][0] = cosf + (1 - cosf) * vec.m_fx * vec.m_fx;
	m_Matrix[0][1] = (1 - cosf) * vec.m_fx * vec.m_fy - sinf * vec.m_fz;
	m_Matrix[0][2] = (1 - cosf)* vec.m_fx * vec.m_fz + sinf * vec.m_fy;
	m_Matrix[1][0] = (1 - cosf) * vec.m_fy * vec.m_fx + sinf * vec.m_fz;
	m_Matrix[1][1] = cosf + (1 - cosf) * vec.m_fy * vec.m_fy;
	m_Matrix[1][2] = (1 - cosf) * vec.m_fy * vec.m_fz - sinf * vec.m_fx;
	m_Matrix[2][0] = (1 - cosf) * vec.m_fz * vec.m_fx - sinf * vec.m_fy;
	m_Matrix[2][1] = (1 - cosf) * vec.m_fy * vec.m_fz + sinf * vec.m_fx;
	m_Matrix[2][2] = cosf + (1 - cosf) * vec.m_fz * vec.m_fz;
}

void Matrix33::ScaleMatrix(float fX, float fY, float fZ)
{
	*this = Identity;
	m_Matrix[0][0] = fX;
	m_Matrix[1][1] = fY;
	m_Matrix[2][2] = fZ;
}

void Matrix33::FromMatrix44(const Matrix44* mat44)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_Matrix[i][j] = mat44->m_Matrix[i][j];
		}
	}
}
