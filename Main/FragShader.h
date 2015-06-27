#pragma once
#include "IResource.h"
#include "RenderEnum.h"
#include "Singleton.h"
namespace ZG
{
	class FragShader;
	class FragShaderDesc
	{
	public:
		SmartPointer<FragShader> m_pFragShader;
		ESTAGESHADERTYPE m_eStageDesc;
		EFRAGSHADERTYPE	m_eFragShaderDesc;
		ELIGHTTYPE		m_eLightType;
		unsigned int	m_nPointLightNum;
		unsigned int	m_nDirLightNum;
		unsigned int	m_nSpotLightNum;
		bool			m_bAmbient;
		FragShaderDesc()
			:m_nPointLightNum(0)
			, m_nDirLightNum(0)
			, m_nSpotLightNum(0)
			, m_eLightType(ELIGHTTYPEINVALIE)
			, m_bAmbient(false)
		{

		}
	};
	class HardwareFragShader;

	template <class T>
	class ResourceManager;
	class MAIN_API FragShader :public IResource
	{
	public:
		FragShader();
		virtual ~FragShader();

		//HardwareFragShader* GetHardwareFragShader(const FragShaderDesc& desc) const;


		const char* m_pCodeBuffer;
		//shader used engine param;
		std::unordered_map<std::string, bool> m_mapEngineParam;
		friend class ResourceManager < FragShader > ;
	};

	extern template class MAIN_API  Singleton < ResourceManager<FragShader> >;
}