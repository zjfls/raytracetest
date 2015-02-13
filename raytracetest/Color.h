#pragma once
//
class Color
{
public:
	Color();
	Color(float R, float G, float B, float A);
	Color(const Color& inColor);
	Color operator=(const Color& inColor);
	Color operator+(const Color& inColor) const;
	Color operator*(float f) const;
	Color operator*(const Color& inColor)const ;
	virtual ~Color();
	float	m_fR;
	float	m_fG;
	float	m_fB;
	float	m_fA;


	const static Color white;
	const static Color black;
	const static Color red;
	const static Color green;
	const static Color blue;
};

