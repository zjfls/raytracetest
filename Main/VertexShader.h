#pragma once
#include "IResource.h"
#include "RenderEnum.h"
#include "Singleton.h"
namespace ZG
{
	template<class T>
	class ResourceManager;

	class VertexShader;
	class MAIN_API VertexShaderDesc
	{
	public:
		SmartPointer<VertexShader>	m_pVertexShader;
		ESTAGESHADERTYPE			m_eStageDesc;
		EVERTEXSHADERTPYE			m_eVShaderDesc;
		bool						m_bSkinInfo;
		int							m_bSkinNum;
	};


	class HardwareVertexShader;
	class MAIN_API VertexShader :public IResource
	{
	public:
		VertexShader();
		virtual ~VertexShader();

		const char* m_pCodeBuffer;
		//std::vector<


		friend class ResourceManager < VertexShader > ;
	};

	extern template class MAIN_API Singleton < ResourceManager<VertexShader> >;
}