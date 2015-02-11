// raytracetest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SimpleWorld.h"
#include "SimpleWorldObj.h"
#include "RayTraceCamera.h"
#include "Vector3.h"
#include "Sphere3D.h"



IWorldObj* CreateSphere3D(float fRadius,const Vector3& vecPos)
{
	IWorldObj* pObj = new SimpleWorldObj();
	Sphere3D* pSphere = new Sphere3D();
	pSphere->m_fRadius = fRadius;
	pObj->addModule(pSphere);
	pObj->m_pTransform->m_vecTranslate = vecPos;
	return pObj;
}

int _tmain(int argc, _TCHAR* argv[])
{
	IWorld* pWorld = new SimpleWorld();
	IWorldObj* pObj = new SimpleWorldObj();
	pObj->m_pTransform->m_vecTranslate = Vector3(0.0f, 0.0f, 0.0f);
	RayTraceCamera* pCamera = new RayTraceCamera;
	pObj->addModule(pCamera);
	//
	IWorldObj* pSphere1 = CreateSphere3D(1000.0f, Vector3(0.0f,-1000.0f,1000.0f));
	IWorldObj* pSphere2 = CreateSphere3D(10.0f, Vector3(10.0f, 0.0f, 1000.0f));
	IWorldObj* pSphere3 = CreateSphere3D(10.0f, Vector3(-10.0f, 0.0f, 1000.0f));
	pWorld->m_pRoot->addChild(pSphere1);
	pWorld->m_pRoot->addChild(pSphere2);
	pWorld->m_pRoot->addChild(pSphere3);
	//
	pWorld->m_pRoot->addChild(pObj);

	//
	pWorld->Update();
	pCamera->Render();
	delete pWorld;
	return 0;
}

