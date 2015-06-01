#pragma once
#include "CameraBase.h"
#include "Matrix44.h"
class WORLD_API RasterCamera :
	public CameraBase
{
public:
	RasterCamera();
	~RasterCamera();
	virtual void Update(SmartPointer<ModuleBase> pModule);

	virtual SmartPointer<ModuleBase> Clone();
	//
	//
};

