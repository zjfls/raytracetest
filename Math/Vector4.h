#pragma once

class Vector3;
class Matrix44;
//Æë´Î×ø±ê
class MATH_API Vector4
{
public:
	Vector4();
	Vector4(float x, float y, float z, float w)
		:m_fx(x)
		, m_fy(y)
		, m_fz(z)
		, m_fw(w)
	{

	}
	~Vector4();


	void Vector3ToPoint(const Vector3& vec3In);
	void Vector3ToDirection(const Vector3& vec3In);
	void ToVector3(Vector3& vecIn) const;
	Vector4 operator*(const Matrix44 mat44)const;

	float m_fx;
	float m_fy;
	float m_fz;
	float m_fw;
};

