#include "stdafx.h"
#include "GizmoManager.h"
#include "IWorldObj.h"
#include "Cone.h"
#include "Cylinder.h"
#include "TranslateGizmo.h"
#include "MaterialResource.h"
#include "Color.h"
using namespace ZG;
template class WORLD_API Singleton < GizmoManager >;
template<> SmartPointer<GizmoManager> Singleton<GizmoManager>::_instance = nullptr;


bool ZG::GizmoManager::Init()
{
	createTranlateGizmo();
	createRotationGizmo();
	createScaleGizmo();
	return true;
}

void ZG::GizmoManager::createTranlateGizmo()
{
	m_pTranslateGizmo = new TranslateGizmo;
	//
	SmartPointer<IWorldObj> pTranslate = IWorldObj::CreateWorldObj();
	//
	m_pTranslateGizmo->m_pRoot = pTranslate;
	//
	SmartPointer<IWorldObj> pTransUP = IWorldObj::CreateWorldObj();
	SmartPointer<IWorldObj> pTransRight = IWorldObj::CreateWorldObj();
	SmartPointer<IWorldObj> pTransForward = IWorldObj::CreateWorldObj();
	pTranslate->addChild(pTransUP);
	pTranslate->addChild(pTransRight);
	pTranslate->addChild(pTransForward);
	//up
	SmartPointer<IWorldObj> pTransUPCylinder = IWorldObj::CreateWorldObj();
	SmartPointer<Cylinder> pCylinder = pTransUPCylinder->addModule<Cylinder>(pTransUPCylinder);
	pCylinder->m_pSharedMaterial = pCylinder->GetDefaultMaterial();
	m_pTranslateGizmo->m_pUpMaterialCylinder = pCylinder->GetMaterialInstance();
	m_pTranslateGizmo->m_pUpMaterialCylinder->SetArg<GameColor>("MainColor",GameColor::red * 0.5f);
	//
	pCylinder->m_fHeight = 50.0f;
	pCylinder->m_fRadius = 3.0f;
	pCylinder->m_nSubdivide = 100;
	pCylinder->GeneratePolygon();
	SmartPointer<IWorldObj> pTransUPCone = IWorldObj::CreateWorldObj();
	SmartPointer<Cone> pCone = pTransUPCone->addModule<Cone>(pTransUPCone);
	pCone->m_pSharedMaterial = pCone->GetDefaultMaterial();
	m_pTranslateGizmo->m_pUpMaterialCone = pCone->GetMaterialInstance();
	m_pTranslateGizmo->m_pUpMaterialCone->SetArg<GameColor>("MainColor", GameColor::red * 0.5f);
	//
	pCone->m_fHeight = 10.0f;
	pCone->m_fRadius = 5.0f;
	pCone->m_nSubdivide = 100;
	pCone->GeneratePolygon();
	pTransUP->addChild(pTransUPCylinder);
	pTransUP->addChild(pTransUPCone);
	pTransUPCone->m_pTransform->SetTranslate(0.0f, 50.0f, 0.0f);
	//right
	SmartPointer<IWorldObj> pTransRightCylinder = IWorldObj::CreateWorldObj();
	pCylinder = pTransRightCylinder->addModule<Cylinder>(pTransRightCylinder);
	pCylinder->m_pSharedMaterial = pCylinder->GetDefaultMaterial();
	m_pTranslateGizmo->m_pRightMaterialCylinder = pCylinder->GetMaterialInstance();
	m_pTranslateGizmo->m_pRightMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::blue * 0.5f);
	//
	pCylinder->m_fHeight = 50.0f;
	pCylinder->m_fRadius = 3.0f;
	pCylinder->m_nSubdivide = 100;
	pCylinder->GeneratePolygon();
	SmartPointer<IWorldObj> pTransRightCone = IWorldObj::CreateWorldObj();
	pCone = pTransRightCone->addModule<Cone>(pTransRightCone);
	pCone->m_pSharedMaterial = pCone->GetDefaultMaterial();
	m_pTranslateGizmo->m_pRightMaterialCone = pCone->GetMaterialInstance();
	m_pTranslateGizmo->m_pRightMaterialCone->SetArg<GameColor>("MainColor", GameColor::blue * 0.5f);
	pCone->m_fHeight = 10.0f;
	pCone->m_fRadius = 5.0f;
	pCone->m_nSubdivide = 100;
	pCone->GeneratePolygon();
	pTransRight->addChild(pTransRightCylinder);
	pTransRight->addChild(pTransRightCone);
	pTransRightCone->m_pTransform->SetTranslate(0.0f, 50.0f, 0.0f);
	pTransRight->m_pTransform->SetOrientation(0.0f, 0.0f, -1.5707f);
	/////////////////////////////////////////////////////////////////////////////////////////forward
	SmartPointer<IWorldObj> pTransForwardCylinder = IWorldObj::CreateWorldObj();
	pCylinder = pTransForwardCylinder->addModule<Cylinder>(pTransForwardCylinder);
	pCylinder->m_pSharedMaterial = pCylinder->GetDefaultMaterial();
	m_pTranslateGizmo->m_pForwardMaterialCylinder = pCylinder->GetMaterialInstance();
	m_pTranslateGizmo->m_pForwardMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::green * 0.5f);
	//
	pCylinder->m_fHeight = 50.0f;
	pCylinder->m_fRadius = 3.0f;
	pCylinder->m_nSubdivide = 100;
	pCylinder->GeneratePolygon();
	SmartPointer<IWorldObj> pTransForwardCone = IWorldObj::CreateWorldObj();
	pCone = pTransForwardCone->addModule<Cone>(pTransForwardCone);
	pCone->m_pSharedMaterial = pCone->GetDefaultMaterial();
	m_pTranslateGizmo->m_pForwardMaterialCone = pCone->GetMaterialInstance();
	m_pTranslateGizmo->m_pForwardMaterialCone->SetArg<GameColor>("MainColor", GameColor::green * 0.5f);
	//
	pCone->m_fHeight = 10.0f;
	pCone->m_fRadius = 5.0f;
	pCone->m_nSubdivide = 100;
	pCone->GeneratePolygon();
	pTransForward->addChild(pTransForwardCylinder);
	pTransForward->addChild(pTransForwardCone);
	pTransForwardCone->m_pTransform->SetTranslate(0.0f, 50.0f, 0.0f);
	pTransForward->m_pTransform->SetOrientation(1.5707f, 0.0f, 0.0f);
}

void ZG::GizmoManager::createRotationGizmo()
{

}

void ZG::GizmoManager::createScaleGizmo()
{

}

ZG::GizmoManager::GizmoManager()
	:m_pTranslateGizmo(nullptr)
{

}

ZG::GizmoManager::~GizmoManager()
{

}
