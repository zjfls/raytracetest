#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight()
{
	m_fRange = 10.0f;
}


PointLight::~PointLight()
{
}

float PointLight::GetIrradiance(const Vector3& vecWorldPosition, const Vector3& vecNormal)
{
	float fRadiance;
	Vector3 vecLightPos = m_pOwnerObj->m_pTransform->GetWorldTranslate();
	Vector3  vecDir = GetLightDirection(vecWorldPosition);
	float fLength = vecDir.length();
	vecDir.normalize();
	if (fLength > m_fRange)
	{
		return 0.0f;
	}
	fRadiance = vecNormal.dot(-vecDir) * m_fIntensity;
	float fAtten = 1.0f / (m_fAttenConst + m_fAttenLinear * fLength + m_fAttenExp * fLength * fLength);
	fRadiance = fRadiance * fAtten;
	fRadiance = std::max(fRadiance, 0.0f);
	return fRadiance;
}

Vector3 PointLight::GetLightDirection(const Vector3& vecWorldPosition)
{
	Vector3 vecDir;
	vecDir = vecWorldPosition - m_pOwnerObj->m_pTransform->GetWorldTranslate();
	vecDir.normalize();
	return vecDir;
}
