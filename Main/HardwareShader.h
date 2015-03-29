#pragma once
class Vector4;
class Matrix44;
class MAIN_API HardwareShader
{
public:
	HardwareShader();
	virtual ~HardwareShader();

	virtual bool SetBool(string strName, const bool bValue) = 0;
	virtual bool SetFloat(string strName, const float fValue) = 0;
	virtual bool SetInt(string strName, const float nValue) = 0;
	virtual bool SetVector(string strName, const Vector4& nValue) = 0;
	virtual bool SetMatrix(string strName, const Matrix44& nValue) = 0;
};

