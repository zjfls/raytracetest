#pragma once
//
class Color
{
public:
	Color();
	Color(float R, float G, float B, float A);
	virtual ~Color();
	float	m_fR;
	float	m_fG;
	float	m_fB;
	float	m_fA;
};

