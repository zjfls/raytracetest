#pragma once
class Vector3
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


	//------------------------------------------------------------------
	float length();
	float distance();
	void normalize();
	bool isNormalized();
	float dot(const Vector3& vecIn) const;
	Vector3 cross(const Vector3& vecIn) const;
	float angle(const Vector3& vecIn) const;
	virtual ~Vector3();
	//------------------------------------------------------------------


	///////////////////////////
	//
	float m_fx;
	float m_fy;
	float m_fz;
	///////////////////////////
};

typedef Vector3 Point3D;
typedef Vector3 Direction3D;
typedef Vector3 Point3D;
