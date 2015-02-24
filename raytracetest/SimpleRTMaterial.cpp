#include "stdafx.h"
#include "SimpleRTMaterial.h"


SimpleRTMaterial::SimpleRTMaterial()
{
		m_bReflection = false;
		m_bRefraction = false;
		m_fRefractiveIndex = 1.0f;
		m_fTransparecy = 0.0f;
}


SimpleRTMaterial::~SimpleRTMaterial()
{
}

