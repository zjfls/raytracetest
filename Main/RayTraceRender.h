#pragma once
#include "IRender.h"
#include "Color.h"
#include "Vector3.h"
//
class RayTraceCamera;
class IWorld;
class IRenderable;


class Ray3D;
class LightBase;
class RayTraceRender :
	public IRender
{
public:
	RayTraceRender();
	virtual ~RayTraceRender();


	virtual int Render(CameraBase* pCammera, IWorld* pWorld);
	////////////////////////////////////////////////////
	//void setViewPlane();


	Color RayTrace(const Ray3D& ray,int nDepth);
	static int MAXDEPTH;
protected:
	bool ShadowRay(const Ray3D& r,LightBase* pLight);
	//
protected:
	RayTraceCamera* m_pCachedCamera;
	IWorld*			m_pCachedWorld;
	std::vector<IRenderable*> m_vecRenderables;
	std::vector<LightBase*> m_vecLights;
};

