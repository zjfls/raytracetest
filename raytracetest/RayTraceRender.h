#pragma once
#include "IRender.h"
//
class RayTraceRender :
	public IRender
{
public:
	RayTraceRender();
	virtual ~RayTraceRender();


	virtual int Render(CameraBase* pCammera, IWorld* pWorld);
	////////////////////////////////////////////////////
	void setViewPlane();
};

