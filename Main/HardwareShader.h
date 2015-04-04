#pragma once
class Vector4;
class Matrix44;
#include "MaterialArg.h"
#include <string>
#include "RenderEnum.h"
class RasterRender;
struct ShaderConstantInfo
{
	std::string  m_strName;
	ECSTREGTYPE	 m_eRegType;
	unsigned int m_nRegIndex;
};
class MAIN_API HardwareShader
{
public:
	HardwareShader();
	virtual ~HardwareShader();

	bool	SetShaderArg(RasterRender* pRender,string strName,MaterialArg* pArg);


	virtual bool SetBool(string strName, const bool bValue) = 0;
	virtual bool SetFloat(string strName, const float fValue) = 0;
	virtual bool SetInt(string strName, const float nValue) = 0;
	virtual bool SetVector(string strName, const Vector4& nValue) = 0;
	virtual bool SetMatrix(string strName, const Matrix44& nValue) = 0;


	std::unordered_map<string, ShaderConstantInfo>& GetContants(){ return m_mapConstants; };
	std::unordered_map<string, ShaderConstantInfo> m_mapConstants;
};

