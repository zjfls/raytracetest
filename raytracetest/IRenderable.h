#pragma once
#include "ModuleBase.h"
class IMaterial;
class IRenderable:public ModuleBase
{
public:
	IRenderable();
	virtual ~IRenderable();


	virtual void Update();


	IMaterial* m_pMaterial;
};

