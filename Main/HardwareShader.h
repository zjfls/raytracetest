#pragma once

#include "MaterialArg.h"
#include <string>
#include "RenderEnum.h"
#include "TextureSampler.h"
namespace ZG
{
	class Vector4;
	class Matrix44;
	class HardwareTexture;
	class RasterRender;
	struct ShaderConstantInfo
	{
		std::string  m_strName;
		ECSTREGTYPE	 m_eRegType;
		unsigned int m_nRegIndex;
	};
	class MAIN_API HardwareShader:public GameObjectBase
	{
	public:
		HardwareShader();
		virtual ~HardwareShader();

		bool	SetShaderArg(RasterRender* pRender, std::string strName, MaterialArg* pArg);
		bool	SetTextureArg(RasterRender* pRender, std::string strName, HardwareTexture* pTexture, ETEXUSETYPE eTexUseType = ETU_DEFAULT);

		virtual bool SetBool(string strName, const bool bValue) = 0;
		virtual bool SetFloat(string strName, const float fValue) = 0;
		virtual bool SetFloatArray(string strName, const float* pData, unsigned int nLenght) = 0;
		virtual bool SetInt(string strName, const int nValue) = 0;
		virtual bool SetVector(string strName, const Vector4& nValue) = 0;
		virtual bool SetMatrix(string strName, const Matrix44& nValue) = 0;
		virtual bool SetMatrixArray(string strName, const Matrix44* pMat, unsigned int nSize) = 0;



		std::unordered_map<string, ShaderConstantInfo>& GetContants(){ return m_mapConstants; };
		std::unordered_map<string, ShaderConstantInfo> m_mapConstants;
	};
}

