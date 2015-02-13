#include "stdafx.h"
#include "Color.h"
const Color Color::black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::white = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::blue = Color(0.0f, 0.0f, 1.0f, 1.0f);


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

Color Color::operator+(const Color& inColor) const
{
	Color cRt;
	cRt.m_fA = m_fA + inColor.m_fA;
	cRt.m_fR = m_fR + inColor.m_fR;
	cRt.m_fG = m_fG + inColor.m_fG;
	cRt.m_fB = m_fB + inColor.m_fB;
	return cRt;
}

Color Color::operator*(float f) const
{
	Color cRt;
	cRt.m_fA = m_fA * f;
	cRt.m_fR = m_fR * f;
	cRt.m_fG = m_fG * f;
	cRt.m_fB = m_fB * f;
	return cRt;
}

Color Color::operator*(const Color& inColor) const
{
	Color cRt;
	cRt.m_fA = m_fA * inColor.m_fA;
	cRt.m_fR = m_fR * inColor.m_fR;
	cRt.m_fG = m_fG * inColor.m_fG;
	cRt.m_fB = m_fB * inColor.m_fB;
	return cRt;
}
