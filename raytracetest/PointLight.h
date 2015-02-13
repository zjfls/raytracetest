#pragma once
#include "LightBase.h"
class PointLight :
	public LightBase
{
public:

	virtual ~PointLight();
private:
	PointLight();
	friend class IWorldObj;


public:
	float m_fRange;
};

