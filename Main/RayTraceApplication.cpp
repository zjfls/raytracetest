#include "stdafx.h"
#include "RayTraceApplication.h"
#include "Sphere3D.h"
#include "SimpleWorldObj.h"
#include "SimpleWorld.h"
#include "SimpleWorld.h"
#include "SimpleWorldObj.h"
#include "RayTraceCamera.h"
#include "Sphere3D.h"
//#include "MaterialManager.h"
#include "LightBase.h"
#include "RayTraceApplication.h"
#include "SimpleRTMaterial.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Plane3D.h"
#include "FbxAppManager.h"
#include <assert.h>
#include "MathDefine.h"
#include "MathFunc.h"

shared_ptr<RayTraceApplication> Singleton<RayTraceApplication>::_instance = nullptr;

RayTraceApplication::RayTraceApplication()
{
}


RayTraceApplication::~RayTraceApplication()
{
}

void RayTraceApplication::OnInit()
{
	m_pWorld = new SimpleWorld;
	assert(FbxAppManager::GetInstance()->Init());

}
shared_ptr<SimpleRTMaterial> CreateMaterial(Color colorEmission, Color colorDiffuse)
{
	shared_ptr<SimpleRTMaterial> pMat(new SimpleRTMaterial());
	pMat->m_ColorEmi = colorEmission;
	pMat->m_ColorDiffuse = colorDiffuse;
	return pMat;
}


IWorldObj* CreateSphere3D(float fRadius, const Vector3& vecPos, Color colorEmission, Color colorDiffuse,bool bReflect,bool bRefract,float ri = 1.0f,float t = 1.0)
{
	IWorldObj* pObj = new SimpleWorldObj();
	Sphere3D* pSphere = (Sphere3D*)pObj->addModule<Sphere3D>();
	pSphere->m_fRadius = fRadius;
	//pObj->addModule(pSphere);
	pObj->m_pTransform->SetTranslate(vecPos.m_fx,vecPos.m_fy,vecPos.m_fz);

	shared_ptr<SimpleRTMaterial> pMat = CreateMaterial(colorEmission, colorDiffuse);
	pMat->m_bReflection = bReflect;
	pMat->m_bRefraction = bRefract;
	pMat->m_fTransparecy = t;
	pMat->m_fRefractiveIndex = ri;
	pSphere->m_pSharedMaterial = pMat;
	return pObj;
}

IWorldObj* AddPlane3D(IWorldObj* pParent)
{
	IWorldObj* pObj = new SimpleWorldObj();
	Plane3D*	pPlane = pObj->addModule<Plane3D>();
	pPlane->m_vecPt = Vector3(0.0f, -100.0f, 0.0f);
	pPlane->m_vecNormal = Vector3(0.0f, 1.0f, 0.0f);
	shared_ptr<SimpleRTMaterial> pMat = CreateMaterial(Color(0.1f,0.1f,0.1f,1.0f), Color(0.4f,0.4f,0.1f,1.0f));
	pPlane->m_pSharedMaterial = pMat;
	pMat->m_bReflection = true;
	pMat->m_fRefractiveIndex = 1.05f;
	pMat->m_bRefraction = true;
	pMat->m_fTransparecy = 0.9f;
	pParent->addChild(pObj);
	return pObj;

	
}


void RayTraceApplication::SetupScene()
{
	IWorld* pWorld = m_pWorld;
	IWorldObj* pObj = new SimpleWorldObj();
	pObj->m_pTransform->SetTranslate(0.0f, 0.0f, -650.0f);// = Vector3(0.0f, 0.0f, 0.0f);
	m_pCamera = (RayTraceCamera*)pObj->addModule<RayTraceCamera>();
	pWorld->m_pRoot->addChild(pObj);

	
	//add directionallight
	IWorldObj* pLightObj = new SimpleWorldObj();
	DirectionalLight* pLight = pLightObj->addModule<DirectionalLight>();
	pLight->m_Color = Color(0.0f, 0.7f, 0.3f, 1.0f);
	pLight->m_fIntensity = 0.5f;
	pLightObj->m_pTransform->SetOrientation(-PI - 1.0f,0.0f,0.0f);
	pWorld->m_pRoot->addChild(pLightObj);
	//
	//add pointlight
	IWorldObj* pPointLightObj = new SimpleWorldObj();
	PointLight* pPointLight = pPointLightObj->addModule<PointLight>();
	pPointLight->m_Color = Color(0.5f, 0.1f, 0.0f, 1.0f);
	pPointLight->m_fIntensity = 8.0f;
	pPointLight->m_fAttenConst = 10.0f;
	pPointLight->m_fAttenLinear = 0.05f;
	pPointLight->m_fAttenExp = 0.0001f;
	pPointLight->m_fRange = 20000.0f;
	pPointLightObj->m_pTransform->SetTranslate(Vector3(0.0f, 250.0f, -250.0f));
	pWorld->m_pRoot->addChild(pPointLightObj);
	//
	//
	IWorldObj* pSphere1 = CreateSphere3D(300.0f, Vector3(0.0f, -300.0f, 333.0f), Color(0.03f, 0.13f, 0.02f, 1.0f), Color::white * 0.5f, true, true);
	IWorldObj* pSphere2 = CreateSphere3D(100.0f, Vector3(0.0f, 100.0f, 0.0f), Color(0.3f, 0.0f, 0.3f, 1.0f), Color::white, true, true);
	IWorldObj* pSphere3 = CreateSphere3D(100.0f, Vector3(-200.0f, 100.0f, 0.0f), Color::blue * 0.2, Color::white,true,true,1.01,0.4);
	pWorld->m_pRoot->addChild(pSphere1);
	pWorld->m_pRoot->addChild(pSphere2);
	pWorld->m_pRoot->addChild(pSphere3);
	IWorldObj* pSphere4 = CreateSphere3D(100.0f, Vector3(-500.0f, -100.0f, 220.0f), Color::blue * 0.2, Color::white, true, true,1.02,0.7);
	pWorld->m_pRoot->addChild(pSphere4);

	IWorldObj* pSphere5 = CreateSphere3D(7000.0f, Vector3(0.0f, -100.0f, 12000.0f), Color(0.23f, 0.23f, 0.02f, 1.0f), Color::white, true, false);
	pWorld->m_pRoot->addChild(pSphere5);

	//add plane
	AddPlane3D(pWorld->m_pRoot);
	//
	m_pCamera->SetPerpViewPort(10, 10000, AngleToRad(atan(1 * 1080.0f / 1920.0f) * 2 * 180 / PI), AngleToRad(90), 192 * 5, 108 * 5);

}
//#include <fbxsdk.h>
//#include "../Common/Common.h"
//#include "../Common/GeometryUtility.h"
void RayTraceApplication::OnEndInit()
{
//	m_pCamera->Render();
}
