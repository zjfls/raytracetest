#pragma once
#include "RayTraceMaterial.h"
#include "Color.h"


namespace ZG
{
	class LightBase;
	class SimpleRTMaterial :
		public RayTraceMaterial
	{
	public:
		SimpleRTMaterial();
		virtual ~SimpleRTMaterial();

		//Color	GetLightContribute(LightBase* pLight);
		GameColor	m_ColorEmi;
		GameColor	m_ColorDiffuse;
		//
		bool	m_bReflection;
		bool	m_bRefraction;
		float	m_fRefractiveIndex;
		float	m_fTransparecy;
		//
	};
}
