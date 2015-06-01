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

SmartPointer<RayTraceApplication> Singleton<RayTraceApplication>::_instance = nullptr;

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
SmartPointer<SimpleRTMaterial> CreateMaterial(GameColor colorEmission, GameColor colorDiffuse)
{
	SmartPointer<SimpleRTMaterial> pMat(new SimpleRTMaterial());
	pMat->m_ColorEmi = colorEmission;
	pMat->m_ColorDiffuse = colorDiffuse;
	return pMat;
}


SmartPointer<IWorldObj> CreateSphere3D(float fRadius, const Vector3& vecPos, GameColor colorEmission, GameColor colorDiffuse,bool bReflect,bool bRefract,float ri = 1.0f,float t = 1.0)
{
	SmartPointer<IWorldObj> pObj = IWorldObj::CreateWorldObj();
	SmartPointer<Sphere3D> pSphere = pObj->addModule<Sphere3D>(pObj);
	pSphere->m_fRadius = fRadius;
	//pObj->addModule(pSphere);
	pObj->m_pTransform->SetTranslate(vecPos.m_fx,vecPos.m_fy,vecPos.m_fz);

	SmartPointer<SimpleRTMaterial> pMat = CreateMaterial(colorEmission, colorDiffuse);
	pMat->m_bReflection = bReflect;
	pMat->m_bRefraction = bRefract;
	pMat->m_fTransparecy = t;
	pMat->m_fRefractiveIndex = ri;
	pSphere->m_pSharedMaterial = pMat.SmartPointerCast<MaterialResource>();
	return pObj;
}

SmartPointer<IWorldObj> AddPlane3D(SmartPointer<IWorldObj> pParent)
{
	SmartPointer<IWorldObj> pObj = IWorldObj::CreateWorldObj();
	SmartPointer<Plane3D>	pPlane = pObj->addModule<Plane3D>(pObj);
	pPlane->m_vecPt = Vector3(0.0f, -100.0f, 0.0f);
	pPlane->m_vecNormal = Vector3(0.0f, 1.0f, 0.0f);
	SmartPointer<SimpleRTMaterial> pMat = CreateMaterial(GameColor(0.1f,0.1f,0.1f,1.0f), GameColor(0.4f,0.4f,0.1f,1.0f));
	pPlane->m_pSharedMaterial = pMat.SmartPointerCast<MaterialResource>();
	pMat->m_bReflection = true;
	pMat->m_fRefractiveIndex = 1.05f;
	pMat->m_bRefraction = true;
	pMat->m_fTransparecy = 0.9f;
	pParent->addChild(pObj);
	return pObj;

	
}


void RayTraceApplication::SetupScene()
{
	SmartPointer<IWorld> pWorld = m_pWorld;
	SmartPointer<IWorldObj> pObj = new SimpleWorldObj();
	pObj->m_pTransform->SetTranslate(0.0f, 0.0f, -650.0f);// = Vector3(0.0f, 0.0f, 0.0f);
	m_pCamera = pObj->addModule<RayTraceCamera>(pObj);
	pWorld->m_pRoot->addChild(pObj);

	
	//add directionallight
	SmartPointer<IWorldObj> pLightObj = IWorldObj::CreateWorldObj();
	SmartPointer<DirectionalLight> pLight = pLightObj->addModule<DirectionalLight>(pLightObj);
	pLight->m_Color = GameColor(0.0f, 0.7f, 0.3f, 1.0f);
	pLight->m_fIntensity = 0.5f;
	pLightObj->m_pTransform->SetOrientation(-PI - 1.0f,0.0f,0.0f);
	pWorld->m_pRoot->addChild(pLightObj);
	//
	//add pointlight
	SmartPointer<IWorldObj> pPointLightObj = IWorldObj::CreateWorldObj();
	SmartPointer<PointLight> pPointLight = pPointLightObj->addModule<PointLight>(pPointLightObj);
	pPointLight->m_Color = GameColor(0.5f, 0.1f, 0.0f, 1.0f);
	pPointLight->m_fIntensity = 8.0f;
	pPointLight->m_fAttenConst = 10.0f;
	pPointLight->m_fAttenLinear = 0.05f;
	pPointLight->m_fAttenExp = 0.0001f;
	pPointLight->m_fRange = 20000.0f;
	pPointLightObj->m_pTransform->SetTranslate(Vector3(0.0f, 250.0f, -250.0f));
	pWorld->m_pRoot->addChild(pPointLightObj);
	//
	//
	SmartPointer<IWorldObj> pSphere1 = CreateSphere3D(300.0f, Vector3(0.0f, -300.0f, 333.0f), GameColor(0.03f, 0.13f, 0.02f, 1.0f), GameColor::white * 0.5f, true, true);
	SmartPointer<IWorldObj> pSphere2 = CreateSphere3D(100.0f, Vector3(0.0f, 100.0f, 0.0f), GameColor(0.3f, 0.0f, 0.3f, 1.0f), GameColor::white, true, true);
	SmartPointer<IWorldObj> pSphere3 = CreateSphere3D(100.0f, Vector3(-200.0f, 100.0f, 0.0f), GameColor::blue * 0.2, GameColor::white, true, true, 1.01, 0.4);
	pWorld->m_pRoot->addChild(pSphere1);
	pWorld->m_pRoot->addChild(pSphere2);
	pWorld->m_pRoot->addChild(pSphere3);
	SmartPointer<IWorldObj> pSphere4 = CreateSphere3D(100.0f, Vector3(-500.0f, -100.0f, 220.0f), GameColor::blue * 0.2, GameColor::white, true, true, 1.02, 0.7);
	pWorld->m_pRoot->addChild(pSphere4);

	SmartPointer<IWorldObj> pSphere5 = CreateSphere3D(7000.0f, Vector3(0.0f, -100.0f, 12000.0f), GameColor(0.23f, 0.23f, 0.02f, 1.0f), GameColor::white, true, false);
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
