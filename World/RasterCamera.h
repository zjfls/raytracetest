#pragma once
#include "CameraBase.h"
#include "Matrix44.h"
class WORLD_API RasterCamera :
	public CameraBase
{
public:
	RasterCamera();
	~RasterCamera();
	virtual void Update(std::shared_ptr<ModuleBase> pModule);

	virtual shared_ptr<ModuleBase> Clone();
	//
	//
};

