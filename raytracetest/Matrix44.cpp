#include "stdafx.h"
#include "Matrix44.h"
#include "Matrix33.h"
const Matrix44 Matrix44::Identity = Matrix44(1, 0, 0, 0,
0, 1, 0, 0,
0, 0, 1, 0,
0, 0, 0, 0 );



Matrix44::Matrix44()
{
	*this = Identity;
}

Matrix44::Matrix44(const Matrix44& matIn)
{

}

Matrix44::Matrix44(float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15, float f16)
{

}


Matrix44::~Matrix44()
{
}

Matrix44 Matrix44::operator=(const Matrix44& matIn)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; i < 4; ++j)
		{
			m_Matrix[i][j] = matIn.m_Matrix[i][j];
		}
	}
	return *this;
}

Matrix44 Matrix44::operator*(const Matrix44& matIn)
{
	Matrix44 matRet;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			matRet.m_Matrix[i][j] = 0.0f;
			for (int ii = 0; ii < 4; ++ii)
			{
				matRet.m_Matrix[i][j] += m_Matrix[i][ii] * matIn.m_Matrix[ii][j];
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
		for (int j = 0; i < 3; ++j)
		{
			m_Matrix[i][j] = mat33->m_Matrix[i][j];
		}
	}
}
