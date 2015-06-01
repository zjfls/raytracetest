#include "stdafx.h"
#include "PointLight.h"
#include "IWorldObj.h"

PointLight::PointLight()
{
	m_eLightType = EPOINTLIGHT;
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
	fRadiance = max(fRadiance, 0.0f);
	return fRadiance;
}

Vector3 PointLight::GetLightDirection(const Vector3& vecWorldPosition)
{
	Vector3 vecDir;
	vecDir = vecWorldPosition - m_pOwnerObj->m_pTransform->GetWorldTranslate();
	vecDir.normalize();
	return vecDir;
}

SmartPointer<ModuleBase> PointLight::Clone()
{
	SmartPointer<PointLight> pLight = SmartPointer<PointLight>(new PointLight);
	pLight->m_strName = m_strName;
	pLight->m_bCastShadow = m_bCastShadow;
	pLight->m_Color = m_Color;
	pLight->m_fIntensity = m_fIntensity;
	pLight->m_fRange = m_fRange;
	pLight->m_fAttenConst = m_fRange;
	pLight->m_fAttenLinear = m_fAttenLinear;
	pLight->m_fAttenExp = m_fAttenExp;
	return pLight.get();
	//float m_fRange;
	//float m_fAttenConst;
	//float m_fAttenLinear;
	//float m_fAttenExp;
}
