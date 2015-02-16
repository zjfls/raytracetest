#pragma once
#include "ModuleBase.h"
#include "Color.h"
class LightBase :
	public ModuleBase
{
public:
	virtual ~LightBase();

	virtual float GetIrradiance(const Vector3& vecWorldPosition, const Vector3& vecNormal) = 0;
	virtual Vector3  GetLightDirection(const Vector3& vecWorldPosition) = 0;
	Color m_Color;
	float m_fIntensity;
	float m_bCastShadow;
protected:
	LightBase();
	//friend class LightBaseCreator;
};


//class LightBaseCreator :public IModuleCreator
//{
//public:
//	LightBaseCreator();
//	virtual ~LightBaseCreator();
//
//	virtual ModuleBase* CreateModule();
//};