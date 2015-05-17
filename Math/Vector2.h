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
	Vector2(const Vector2& v)
	{
		m_fx = v.m_fx;
		m_fy = v.m_fy;
	}
	virtual ~Vector2();
	Vector2 operator-(const Vector2& v);

	float m_fx;
	float m_fy;
};

