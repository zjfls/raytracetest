#pragma once
#include "LightBase.h"
class DirectionalLight :
	public LightBase
{
public:
	virtual ~DirectionalLight();
private:
	DirectionalLight();
	friend class IWorldObj;
};
