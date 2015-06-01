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
template<> shared_ptr<GizmoManager> Singleton<GizmoManager>::_instance = nullptr;


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
	shared_ptr<IWorldObj> pTranslate = IWorldObj::CreateWorldObj();
	//
	m_pTranslateGizmo->m_pRoot = pTranslate;
	//
	shared_ptr<IWorldObj> pTransUP = IWorldObj::CreateWorldObj();
	shared_ptr<IWorldObj> pTransRight = IWorldObj::CreateWorldObj();
	shared_ptr<IWorldObj> pTransForward = IWorldObj::CreateWorldObj();
	pTranslate->addChild(pTransUP);
	pTranslate->addChild(pTransRight);
	pTranslate->addChild(pTransForward);
	//up
	shared_ptr<IWorldObj> pTransUPCylinder = IWorldObj::CreateWorldObj();
	shared_ptr<Cylinder> pCylinder = pTransUPCylinder->addModule<Cylinder>(pTransUPCylinder);
	pCylinder->m_pSharedMaterial = pCylinder->GetDefaultMaterial();
	m_pTranslateGizmo->m_pUpMaterialCylinder = pCylinder->GetMaterialInstance();
	m_pTranslateGizmo->m_pUpMaterialCylinder->SetArg<GameColor>("MainColor",GameColor::red * 0.5f);
	//
	pCylinder->m_fHeight = 50.0f;
	pCylinder->m_fRadius = 3.0f;
	pCylinder->m_nSubdivide = 100;
	pCylinder->GeneratePolygon();
	shared_ptr<IWorldObj> pTransUPCone = IWorldObj::CreateWorldObj();
	shared_ptr<Cone> pCone = pTransUPCone->addModule<Cone>(pTransUPCone);
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
	//forward
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
