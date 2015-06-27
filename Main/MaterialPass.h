#pragma once
#include "ResourceManager.h"
#include "GameObjectBase.h"
#include "RenderEnum.h"
#include "RenderBaseClass.h"
#include <vector>

namespace ZG
{ 
	class VertexShader;
	class FragShader;
	class MAIN_API MaterialPass :public GameObjectBase
	{
	public:
		MaterialPass();
		virtual ~MaterialPass();

		MaterialPass* clone();
		void	SetRenderState(stRenderState state);

		
		std::vector<stRenderState> m_vecRenderState;
		//
		//	//
		SmartPointer<VertexShader> m_pVertexShader;
		//
		SmartPointer<FragShader>	m_pFragShader;
		//
		EVERTEXSHADERTPYE	m_eVertexShaderType;
		EFRAGSHADERTYPE		m_eFragShaderType;
	};
}


