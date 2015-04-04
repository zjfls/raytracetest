#pragma once
class MATH_API Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& in);




	Vector3 operator=(const Vector3& vecIn);
	bool operator==(const Vector3& vecIn) const;
	Vector3	operator+(const Vector3& vecIn) const;
	Vector3 operator-(const Vector3& vecIn) const;
	Vector3 operator*(float f) const;
	Vector3 operator-() const;
	Vector3 operator+=(const Vector3& vecIn);


	//------------------------------------------------------------------
	float length() const;
	float distance(const Vector3& vecTarget) const;
	Vector3 normalize();
	bool isNormalized() const;
	float dot(const Vector3& vecIn) const;
	Vector3 cross(const Vector3& vecIn) const;
	float angle(const Vector3& vecIn) const;
	~Vector3();
	//------------------------------------------------------------------


	///////////////////////////
	//
	float m_fx;
	float m_fy;
	float m_fz;
	///////////////////////////
	static const Vector3	ZERO;
	static const Vector3	ONE;
	static const Vector3	XAxis;
	static const Vector3	YAxis;
	static const Vector3	ZAxis;
};

typedef Vector3 Point3D;
typedef Vector3 Direction3D;
typedef Vector3 Point3D;


inline Vector3 operator*(float f, const Vector3& vecIn)
{
	return vecIn * f;
}