#pragma once
#include "RayTraceMaterial.h"
#include "Color.h"
class SimpleRTMaterial :
	public RayTraceMaterial
{
public:
	SimpleRTMaterial();
	virtual ~SimpleRTMaterial();


	Color	m_ColorEmi;
	Color	m_ColorDiffuse;
	bool	m_bReflection;
	bool	m_bRefraction;
};

