#pragma once
#include "CameraBase.h"
class RayTraceCamera:public CameraBase
{
public:
	RayTraceCamera();
	virtual ~RayTraceCamera();

	virtual void Update();
	virtual void OnLateUpdate();
	virtual void Render();
////////////////////////////////////////////////////////////

};

