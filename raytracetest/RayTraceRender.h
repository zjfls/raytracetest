#pragma once
#include "IRender.h"
#include "Color.h"
#include "Vector3.h"
//
class RayTraceCamera;
class IWorld;
class IRenderable;
class RayTraceRender :
	public IRender
{
public:
	RayTraceRender();
	virtual ~RayTraceRender();


	virtual int Render(CameraBase* pCammera, IWorld* pWorld);
	////////////////////////////////////////////////////
	//void setViewPlane();


	Color RayTrace(const Vector3& vecTarget);
	//
protected:
	RayTraceCamera* m_pCachedCamera;
	IWorld*			m_pCachedWorld;
	std::vector<IRenderable*> m_vecRenderables;
};

