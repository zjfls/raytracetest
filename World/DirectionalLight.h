#pragma once
#include "LightBase.h"
class WORLD_API DirectionalLight :
	public LightBase
{
public:
	virtual ~DirectionalLight();
	virtual float GetIrradiance(const Vector3& vecWorldPosition, const Vector3& vecNormal);
	virtual Vector3  GetLightDirection(const Vector3& vecWorldPosition);
	virtual ModuleBase* Clone()
	{ 
		DirectionalLight* pLight = new DirectionalLight;
		pLight->m_strName = m_strName;
		pLight->m_bCastShadow = m_bCastShadow;
		pLight->m_Color = m_Color;
		pLight->m_fIntensity = m_fIntensity;
		return pLight;
	};
private:
	DirectionalLight();
	friend class IWorldObj;
};
