#pragma once
#include "ModuleBase.h"
class MaterialResource;
class IRenderable:public ModuleBase
{
public:
	IRenderable();
	virtual ~IRenderable();


	virtual void Update();


	shared_ptr<MaterialResource> m_pMaterial;
};

