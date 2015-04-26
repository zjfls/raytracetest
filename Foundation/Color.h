#pragma once
//
class FOUNDATION_API GameColor
{
public:
	GameColor();
	GameColor(float R, float G, float B, float A);
	GameColor(const GameColor& inColor);
	GameColor operator=(const GameColor& inColor);
	GameColor operator+(const GameColor& inColor) const;
	GameColor operator*(float f) const;
	GameColor operator*(const GameColor& inColor)const ;
	virtual ~GameColor();
	float	m_fR;
	float	m_fG;
	float	m_fB;
	float	m_fA;


	const static GameColor white;
	const static GameColor black;
	const static GameColor red;
	const static GameColor green;
	const static GameColor blue;
};

