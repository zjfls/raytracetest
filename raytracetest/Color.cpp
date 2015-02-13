#include "stdafx.h"
#include "Color.h"
const Color Color::black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::white = Color(1.0f, 1.0f, 1.0f, 1.0f);

Color::Color()
{
}

Color::Color(float R, float G, float B, float A)
{
	m_fR = R;
	m_fG = G;
	m_fB = B;
	m_fA = A;
}

Color::Color(const Color& inColor)
{
	m_fR = inColor.m_fR;
	m_fG = inColor.m_fG;
	m_fB = inColor.m_fB;
	m_fA = inColor.m_fA;
}


Color::~Color()
{
}

Color Color::operator=(const Color& inColor)
{
	m_fR = inColor.m_fR;
	m_fG = inColor.m_fG;
	m_fB = inColor.m_fB;
	m_fA = inColor.m_fA;


	return *this;
}
