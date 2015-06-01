#include "stdafx.h"
#include "DirectionalLight.h"
#include "IWorldObj.h"

DirectionalLight::DirectionalLight()
{
	m_eLightType = EDIRLIGHT;
}


DirectionalLight::~DirectionalLight()
{
}

float DirectionalLight::GetIrradiance(const Vector3& vecWorldPosition, const Vector3& vecNormal)
{
	Vector3 lightDir = GetLightDirection(vecWorldPosition);
	float fRadiance = vecNormal.dot(-lightDir) * m_fIntensity;
	fRadiance = max(fRadiance, 0.0f);
	return fRadiance;
}

Vector3 DirectionalLight::GetLightDirection(const Vector3& vecWorldPosition)
{
	Vector3 vecDir = m_pOwnerObj->m_pTransform->GetForward();
	vecDir.normalize();
	return vecDir;
}

SmartPointer<ModuleBase> DirectionalLight::Clone()
{
	SmartPointer<DirectionalLight> pLight = SmartPointer<DirectionalLight>(new DirectionalLight);
	pLight->m_strName = m_strName;
	pLight->m_bCastShadow = m_bCastShadow;
	pLight->m_Color = m_Color;
	pLight->m_fIntensity = m_fIntensity;
	return pLight.get();
};
