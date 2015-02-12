#pragma once
#include "RayTraceViewPort.h"

//垂直矩形视口
class RayTracePerpViewPort :
	public RayTraceViewPort
{
public:
	RayTracePerpViewPort();
	RayTracePerpViewPort(const Point3D& vecPt,const Direction3D& vecNormal,float fVertFov,float fHorzFov,int pixWidth,int pixHeight);
	virtual ~RayTracePerpViewPort();

private:
	float m_fVertFov;
	float m_fHorzFov;



};

