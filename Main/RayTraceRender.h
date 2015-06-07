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
	virtual void UpdateProjCamera(SmartPointer<CameraBase> pCamera){};

	virtual int Render(SmartPointer<CameraBase> pCammera, SmartPointer<IWorld> pWorld);
	////////////////////////////////////////////////////
	//void setViewPlane();


	GameColor RayTrace(const Ray3D& ray,int nDepth);
	static int MAXDEPTH;
protected:
	bool ShadowRay(const Ray3D& r,SmartPointer<LightBase> pLight);
	//
protected:
	SmartPointer<RayTraceCamera> m_pCachedCamera;
	SmartPointer<IWorld>			m_pCachedWorld;
	std::vector<SmartPointer<IRenderable>> m_vecRenderables;
	std::vector<SmartPointer<LightBase>> m_vecLights;
};

