#pragma once
class MATH_API Vector2
{
public:
	Vector2();
	Vector2(float x, float y)
		:m_fx(x)
		, m_fy(y)
	{

	}
	virtual ~Vector2();

	float m_fx;
	float m_fy;
};

