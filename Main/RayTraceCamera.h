#pragma once
#include "CameraBase.h"
class RayTraceViewPort;
class MAIN_API RayTraceCamera :public CameraBase
{
public:
	//RayTraceCamera();
	virtual ~RayTraceCamera();

	virtual void Update();
	virtual void OnLateUpdate();
	virtual void Render();
////////////////////////////////////////////////////////////
	void SetPerpViewPort(float fNear, float fFar, float fVertFov, float fHorzFov,int pixWidth,int pixHeight);
	const RayTraceViewPort*	GetPerpViewPort(){ return m_pViewPort; };

	
private:
	RayTraceViewPort* m_pViewPort;
	RayTraceCamera();
	//friend class RayTraceCameraCreator;
	friend class IWorldObj;
};



//class RayTraceCameraCreator :public IModuleCreator
//{
//public:
//	RayTraceCameraCreator();
//	virtual ~RayTraceCameraCreator();
//
//	virtual ModuleBase* CreateModule();
//};