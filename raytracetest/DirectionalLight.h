#pragma once
#include "LightBase.h"
class DirectionalLight :
	public LightBase
{
public:
	virtual ~DirectionalLight();
	virtual float GetIrradiance(const Vector3& vecWorldPosition, const Vector3& vecNormal);
	virtual Vector3  GetLightDirection(const Vector3& vecWorldPosition);
private:
	DirectionalLight();
	friend class IWorldObj;
};
