#pragma once
#include "CameraBase.h"
class RayTraceViewPort;
class RayTraceCamera:public CameraBase
{
public:
	RayTraceCamera();
	virtual ~RayTraceCamera();

	virtual void Update();
	virtual void OnLateUpdate();
	virtual void Render();
////////////////////////////////////////////////////////////
	void SetPerpViewPort(float fNear, float fFar, float fVertFov, float fHorzFov,int pixWidth,int pixHeight);


	RayTraceViewPort* m_pViewPort;

};

