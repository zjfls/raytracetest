#include "stdafx.h"
#include "Color.h"
const GameColor GameColor::black = GameColor(0.0f, 0.0f, 0.0f, 1.0f);
const GameColor GameColor::white = GameColor(1.0f, 1.0f, 1.0f, 1.0f);
const GameColor GameColor::red = GameColor(1.0f, 0.0f, 0.0f, 1.0f);
const GameColor GameColor::green = GameColor(0.0f, 1.0f, 0.0f, 1.0f);
const GameColor GameColor::blue = GameColor(0.0f, 0.0f, 1.0f, 1.0f);


GameColor::GameColor()
{
	m_fA = m_fB = m_fG = m_fR = 0.0f;
}

GameColor::GameColor(float R, float G, float B, float A)
{
	m_fR = R;
	m_fG = G;
	m_fB = B;
	m_fA = A;
}

GameColor::GameColor(const GameColor& inColor)
{
	m_fR = inColor.m_fR;
	m_fG = inColor.m_fG;
	m_fB = inColor.m_fB;
	m_fA = inColor.m_fA;
}


GameColor::~GameColor()
{
}

GameColor GameColor::operator=(const GameColor& inColor)
{
	m_fR = inColor.m_fR;
	m_fG = inColor.m_fG;
	m_fB = inColor.m_fB;
	m_fA = inColor.m_fA;


	return *this;
}

GameColor GameColor::operator+(const GameColor& inColor) const
{
	GameColor cRt;
	cRt.m_fA = m_fA + inColor.m_fA;
	cRt.m_fR = m_fR + inColor.m_fR;
	cRt.m_fG = m_fG + inColor.m_fG;
	cRt.m_fB = m_fB + inColor.m_fB;
	return cRt;
}

GameColor GameColor::operator*(float f) const
{
	GameColor cRt;
	cRt.m_fA = m_fA * f;
	cRt.m_fR = m_fR * f;
	cRt.m_fG = m_fG * f;
	cRt.m_fB = m_fB * f;
	return cRt;
}

GameColor GameColor::operator*(const GameColor& inColor) const
{
	GameColor cRt;
	cRt.m_fA = m_fA * inColor.m_fA;
	cRt.m_fR = m_fR * inColor.m_fR;
	cRt.m_fG = m_fG * inColor.m_fG;
	cRt.m_fB = m_fB * inColor.m_fB;
	return cRt;
}
