#include "stdafx.h"
#include "DirectionalLight.h"


DirectionalLight::DirectionalLight()
{
}


DirectionalLight::~DirectionalLight()
{
}

float DirectionalLight::GetIrradiance(const Vector3& vecWorldPosition, const Vector3& vecNormal)
{
	Vector3 lightDir = GetLightDirection(vecWorldPosition);
	float fRadiance = vecNormal.dot(-lightDir) * m_fIntensity;
	fRadiance = std::max(fRadiance, 0.0f);
	return fRadiance;
}

Vector3 DirectionalLight::GetLightDirection(const Vector3& vecWorldPosition)
{
	Vector3 vecDir = m_pOwnerObj->m_pTransform->GetForward();
	vecDir.normalize();
	return vecDir;
}
