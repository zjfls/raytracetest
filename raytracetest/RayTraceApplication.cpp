#include "stdafx.h"
#include "RayTraceApplication.h"
#include "Sphere3D.h"
#include "SimpleWorldObj.h"
#include "SimpleWorld.h"
#include "SimpleWorld.h"
#include "SimpleWorldObj.h"
#include "RayTraceCamera.h"
#include "Vector3.h"
#include "Sphere3D.h"
#include "MaterialManager.h"
#include "LightBase.h"
#include "RayTraceApplication.h"
#include "SimpleRTMaterial.h"
#include "DirectionalLight.h"

RayTraceApplication* Singleton<RayTraceApplication>::_instance = nullptr;

RayTraceApplication::RayTraceApplication()
{
}


RayTraceApplication::~RayTraceApplication()
{
}

void RayTraceApplication::OnInit()
{
	m_pWorld = new SimpleWorld;
}
SimpleRTMaterial* CreateMaterial(Color colorEmission, Color colorDiffuse)
{
	SimpleRTMaterial* pMat = new SimpleRTMaterial();
	pMat->m_ColorEmi = colorEmission;
	pMat->m_ColorDiffuse = colorDiffuse;
	return pMat;
}


IWorldObj* CreateSphere3D(float fRadius, const Vector3& vecPos, Color colorEmission, Color colorDiffuse)
{
	IWorldObj* pObj = new SimpleWorldObj();
	Sphere3D* pSphere = (Sphere3D*)pObj->addModule<Sphere3D>();
	pSphere->m_fRadius = fRadius;
	//pObj->addModule(pSphere);
	pObj->m_pTransform->SetTranslate(vecPos.m_fx,vecPos.m_fy,vecPos.m_fz);

	SimpleRTMaterial* pMat = CreateMaterial(colorEmission, colorDiffuse);
	pSphere->m_pMaterial = pMat;
	return pObj;
}



void RayTraceApplication::OnSetupScene()
{
	IWorld* pWorld = m_pWorld;
	IWorldObj* pObj = new SimpleWorldObj();
	pObj->m_pTransform->SetTranslate(0.0f, 0.0f, 0.0f);// = Vector3(0.0f, 0.0f, 0.0f);
	m_pCamera = (RayTraceCamera*)pObj->addModule<RayTraceCamera>();
	//
	IWorldObj* pLightObj = new SimpleWorldObj();
	DirectionalLight* pLight = pLightObj->addModule<DirectionalLight>();
	pLight->m_Color = Color(0.3f, 0.7f, 0.3f, 1.0f);
	pLight->m_fIntensity = 1.0f;
	pLightObj->m_pTransform->SetOrientation(-PI - 1.0f,0.0f,0.0f);
	pWorld->m_pRoot->addChild(pLightObj);
	//
	IWorldObj* pSphere1 = CreateSphere3D(300.0f, Vector3(0.0f, -300.0f, 700.0f), Color(0.03f, 0.13f, 0.02f, 1.0f), Color::white * 0.5f);
	IWorldObj* pSphere2 = CreateSphere3D(100.0f, Vector3(100.0f, 100.0f, 700.0f), Color(0.3f,0.0f,0.3f,1.0f)*0.5f, Color::white);
	IWorldObj* pSphere3 = CreateSphere3D(100.0f, Vector3(-100.0f, 100.0f, 700.0f), Color::black*0.5f, Color::white);
	pWorld->m_pRoot->addChild(pSphere1);
	pWorld->m_pRoot->addChild(pSphere2);
	pWorld->m_pRoot->addChild(pSphere3);
	pWorld->m_pRoot->addChild(pObj);
	m_pCamera->SetPerpViewPort(10, 10000, AngleToRad(90), AngleToRad(90), 1600, 1200);

}

void RayTraceApplication::OnEndInit()
{
	
	m_pCamera->Render();
}
