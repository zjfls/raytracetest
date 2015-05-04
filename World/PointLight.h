#pragma once
#include "LightBase.h"
class WORLD_API PointLight :
	public LightBase
{
public:
	virtual ~PointLight();
	virtual Vector3  GetLightDirection(const Vector3& vecWorldPosition);
	virtual float GetIrradiance(const Vector3& vecWorldPosition, const Vector3& vecNormal);
	virtual shared_ptr<ModuleBase> Clone();
private:
	PointLight();
	friend class IWorldObj;


public:
	float m_fRange;
	float m_fAttenConst;
	float m_fAttenLinear;
	float m_fAttenExp;
};

