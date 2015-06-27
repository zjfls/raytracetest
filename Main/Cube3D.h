#pragma once
#include "IRenderable.h"
class MAIN_API Cube3D :public IRenderable
{
public:
	Cube3D();
	virtual ~Cube3D();

	virtual void OnUpdate();
};

