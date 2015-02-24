#pragma once
#include "RayTraceMaterial.h"
#include "Color.h"



class LightBase;
class SimpleRTMaterial :
	public RayTraceMaterial
{
public:
	SimpleRTMaterial();
	virtual ~SimpleRTMaterial();

	//Color	GetLightContribute(LightBase* pLight);
	Color	m_ColorEmi;
	Color	m_ColorDiffuse;
	//
	bool	m_bReflection;
	bool	m_bRefraction;
	float	m_fRefractiveIndex;
	float	m_fTransparecy;
	//
};

