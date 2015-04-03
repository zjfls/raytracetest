#pragma once
class Vector4;
class Matrix44;
#include "MaterialArg.h"
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


	std::map<string, EMATARGTYPE>& GetContants(){ return m_mapConstants; };
	std::map<string, EMATARGTYPE> m_mapConstants;
};

