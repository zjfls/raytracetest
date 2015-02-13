#pragma once
#include "ModuleBase.h"
#include "Color.h"
class LightBase :
	public ModuleBase
{
public:
	virtual ~LightBase();
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