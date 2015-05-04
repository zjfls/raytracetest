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


	virtual int Render(std::shared_ptr<CameraBase> pCammera, std::shared_ptr<IWorld> pWorld);
	////////////////////////////////////////////////////
	//void setViewPlane();


	GameColor RayTrace(const Ray3D& ray,int nDepth);
	static int MAXDEPTH;
protected:
	bool ShadowRay(const Ray3D& r,std::shared_ptr<LightBase> pLight);
	//
protected:
	std::shared_ptr<RayTraceCamera> m_pCachedCamera;
	std::shared_ptr<IWorld>			m_pCachedWorld;
	std::vector<std::shared_ptr<IRenderable>> m_vecRenderables;
	std::vector<std::shared_ptr<LightBase>> m_vecLights;
};

