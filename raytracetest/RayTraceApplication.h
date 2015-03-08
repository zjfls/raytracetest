#pragma once
#include "ApplicationBase.h"
class RayTraceCamera;
class RayTraceApplication:public ApplicationBase,public Singleton<RayTraceApplication>
{
public:
	~RayTraceApplication();

	virtual void OnInit();
	virtual void SetupScene();
	virtual void OnEndInit();
	//virtual void PreUpdate();
	//virtual void OnUpdate();
protected:
	RayTraceApplication();
	friend class Singleton<RayTraceApplication>;
private:
	RayTraceCamera* m_pCamera;
};

