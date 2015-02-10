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
	void normalize();
	bool isNormalized();
	float dot(const Vector3& vecIn) const;
	Vector3 cross(const Vector3& vecIn) const;
	virtual ~Vector3();


	///////////////////////////
	//
	float x;
	float y;
	float z;
	///////////////////////////
};

