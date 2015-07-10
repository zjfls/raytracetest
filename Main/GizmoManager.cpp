#include "stdafx.h"
#include "GizmoManager.h"
#include "IWorldObj.h"
#include "Cone.h"
#include "Cylinder.h"
#include "TranslateGizmo.h"
#include "MaterialResource.h"
#include "Color.h"
#include "DynamicVertexData.h"
#include "IWorldObj.h"
#include "RasterMaterial.h"
#include "MaterialPass.h"
#include <string>
#include "materialpass.h"
#include "SkeletonObj.h"
#include "skeleton.h"
#include "SkeletonResource.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "Mesh.h"
#include "AnimationTrack.h"
#include "MeshResource.h"


template class MAIN_API Singleton < GizmoManager >;
template<> SmartPointer<GizmoManager> Singleton<GizmoManager>::_instance = nullptr;


bool ZG::GizmoManager::Init()
{
	createTranlateGizmo();
	createRotationGizmo();
	createScaleGizmo();
	createSceneGridGizmo();
	return true;
}

void ZG::GizmoManager::createTranlateGizmo()
{
	m_pTranslateGizmo = new TranslateGizmo;
	//
	SmartPointer<IWorldObj> pTranslate = new IWorldObj;
	//
	m_pTranslateGizmo->m_pRoot = pTranslate;
	//
	SmartPointer<IWorldObj> pTransUP = new IWorldObj;
	SmartPointer<IWorldObj> pTransRight = new IWorldObj;
	SmartPointer<IWorldObj> pTransForward = new IWorldObj;
	pTranslate->addChild(pTransUP);
	pTranslate->addChild(pTransRight);
	pTranslate->addChild(pTransForward);
	m_pTranslateGizmo->m_pUp = pTransUP;
	m_pTranslateGizmo->m_pRight = pTransRight;
	m_pTranslateGizmo->m_pForward = pTransForward;


	//up
	SmartPointer<IWorldObj> pTransUPCylinder = new IWorldObj;
	pTransUPCylinder->m_strName = "UpCylinder";
	SmartPointer<Cylinder> pCylinder = pTransUPCylinder->addModule<Cylinder>();
	pCylinder->m_strName = "UPCylinder";
	pCylinder->m_pSharedMaterial = pCylinder->GetDefaultMaterial();
	m_pTranslateGizmo->m_pUpMaterialCylinder = pCylinder->GetMaterialInstance();
	m_pTranslateGizmo->m_pUpMaterialCylinder->SetArg<GameColor>("MainColor",GameColor::red * 0.5f);
	//

	//
	pCylinder->m_fHeight = 50.0f;
	pCylinder->m_fRadius = 1.0f;
	pCylinder->m_nSubdivide = 100;
	pCylinder->GeneratePolygon();
	SmartPointer<IWorldObj> pTransUPCone = new IWorldObj;
	SmartPointer<Cone> pCone = pTransUPCone->addModule<Cone>();
	pCone->m_strName = "UPCone";
	pCone->m_pSharedMaterial = pCone->GetDefaultMaterial();
	m_pTranslateGizmo->m_pUpMaterialCone = pCone->GetMaterialInstance();
	m_pTranslateGizmo->m_pUpMaterialCone->SetArg<GameColor>("MainColor", GameColor::red * 0.5f);
	//
	pCone->m_fHeight = 10.0f;
	pCone->m_fRadius = 3.5f;
	pCone->m_nSubdivide = 100;
	pCone->GeneratePolygon();
	pTransUP->addChild(pTransUPCylinder);
	pTransUP->addChild(pTransUPCone);
	pTransUPCone->m_pTransform->SetTranslate(0.0f, 50.0f, 0.0f);
	//right
	SmartPointer<IWorldObj> pTransRightCylinder = new IWorldObj;
	pCylinder = pTransRightCylinder->addModule<Cylinder>();
	pCylinder->m_strName = "RIGHTCylinder";
	pCylinder->m_pSharedMaterial = pCylinder->GetDefaultMaterial();
	m_pTranslateGizmo->m_pRightMaterialCylinder = pCylinder->GetMaterialInstance();
	m_pTranslateGizmo->m_pRightMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::blue * 0.5f);
	//
	pCylinder->m_fHeight = 50.0f;
	pCylinder->m_fRadius = 1.0f;
	pCylinder->m_nSubdivide = 100;
	pCylinder->GeneratePolygon();
	SmartPointer<IWorldObj> pTransRightCone = new IWorldObj;
	pCone = pTransRightCone->addModule<Cone>();
	pCone->m_strName = "RIGHTCone";
	pCone->m_pSharedMaterial = pCone->GetDefaultMaterial();
	m_pTranslateGizmo->m_pRightMaterialCone = pCone->GetMaterialInstance();
	m_pTranslateGizmo->m_pRightMaterialCone->SetArg<GameColor>("MainColor", GameColor::blue * 0.5f);
	pCone->m_fHeight = 10.0f;
	pCone->m_fRadius = 3.5f;
	pCone->m_nSubdivide = 100;
	pCone->GeneratePolygon();
	pTransRight->addChild(pTransRightCylinder);
	pTransRight->addChild(pTransRightCone);
	pTransRightCone->m_pTransform->SetTranslate(0.0f, 50.0f, 0.0f);
	pTransRight->m_pTransform->SetOrientation(0.0f, 0.0f, -1.5707f);
	/////////////////////////////////////////////////////////////////////////////////////////forward
	SmartPointer<IWorldObj> pTransForwardCylinder = new IWorldObj;
	pCylinder = pTransForwardCylinder->addModule<Cylinder>();
	pCylinder->m_strName = "FORWARDCylinder";
	pCylinder->m_pSharedMaterial = pCylinder->GetDefaultMaterial();
	m_pTranslateGizmo->m_pForwardMaterialCylinder = pCylinder->GetMaterialInstance();
	m_pTranslateGizmo->m_pForwardMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::green * 0.5f);
	//
	pCylinder->m_fHeight = 50.0f;
	pCylinder->m_fRadius = 1.0f;
	pCylinder->m_nSubdivide = 100;
	pCylinder->GeneratePolygon();
	SmartPointer<IWorldObj> pTransForwardCone = new IWorldObj;
	pCone = pTransForwardCone->addModule<Cone>();
	pCone->m_strName = "FORWARDCone";
	pCone->m_pSharedMaterial = pCone->GetDefaultMaterial();
	m_pTranslateGizmo->m_pForwardMaterialCone = pCone->GetMaterialInstance();
	m_pTranslateGizmo->m_pForwardMaterialCone->SetArg<GameColor>("MainColor", GameColor::green * 0.5f);
	//
	pCone->m_fHeight = 10.0f;
	pCone->m_fRadius = 3.5f;
	pCone->m_nSubdivide = 100;
	pCone->GeneratePolygon();
	pTransForward->addChild(pTransForwardCylinder);
	pTransForward->addChild(pTransForwardCone);
	pTransForwardCone->m_pTransform->SetTranslate(0.0f, 50.0f, 0.0f);
	pTransForward->m_pTransform->SetOrientation(1.5707f, 0.0f, 0.0f);

	stRenderState s;
	s.m_eRenderState = ZTEST;
	s.m_nValue = 0;
	dynamic_cast<RasterMaterial*>(m_pTranslateGizmo->m_pUpMaterialCylinder.get())->SetRenderState(s);
	dynamic_cast<RasterMaterial*>(m_pTranslateGizmo->m_pUpMaterialCone.get())->SetRenderState(s);
	dynamic_cast<RasterMaterial*>(m_pTranslateGizmo->m_pRightMaterialCylinder.get())->SetRenderState(s);
	dynamic_cast<RasterMaterial*>(m_pTranslateGizmo->m_pRightMaterialCone.get())->SetRenderState(s);
	dynamic_cast<RasterMaterial*>(m_pTranslateGizmo->m_pForwardMaterialCylinder.get())->SetRenderState(s);
	dynamic_cast<RasterMaterial*>(m_pTranslateGizmo->m_pForwardMaterialCone.get())->SetRenderState(s);
}

void ZG::GizmoManager::createRotationGizmo()
{

}

void ZG::GizmoManager::createScaleGizmo()
{

}

ZG::GizmoManager::GizmoManager()
	:m_pTranslateGizmo(nullptr)
	, m_pSceneGrid(nullptr)
{

}

ZG::GizmoManager::~GizmoManager()
{

}

void ZG::GizmoManager::createSceneGridGizmo()
{
	if (m_pSceneGrid != nullptr)
	{
		m_pSceneGrid = nullptr;
	}
	m_pSceneGrid = new IWorldObj;
	m_pSceneGrid->m_strName = "GridObject";
	IRenderable* pSceneGridRenderable = m_pSceneGrid->addModule<IRenderable>().get();
	pSceneGridRenderable->m_pSharedMaterial = pSceneGridRenderable->GetDefaultMaterial();
	
	pSceneGridRenderable->GetMaterialInstance()->SetArg<GameColor>("MainColor", GameColor::white * 0.3f);
	RasterMaterial* mat = (RasterMaterial*)pSceneGridRenderable->GetMaterialInstance().get();
	for each (std::pair<std::string, ZG::SmartPointer<ZG::MaterialPass>> p in mat->m_MaterialPass)
	{
		bool bFoundZTest = false;
		for each (stRenderState var in p.second->m_vecRenderState)
		{
			if (var.m_eRenderState == ZTEST)
			{
				bFoundZTest = true;
				var.m_nValue = 1;
			}
		}
		if (bFoundZTest == false)
		{
			
			stRenderState s;
			s.m_eRenderState = ZTEST;
			s.m_nValue = 1;
			p.second->m_vecRenderState.push_back(s);
			//s.m_eRenderState = ZFUNC;
		}
	}
	//
	int nSubdivide = 100;
	float fInterval = 30;
	DynamicVertexData* dVertexData = new DynamicVertexData;
	pSceneGridRenderable->m_pVertexData = dVertexData;
	pSceneGridRenderable->m_strName = "GridData";
	for (int i = 0; i < nSubdivide + 1; ++i)
	{
		float x, y, z;
		x = (-nSubdivide / 2 + i) * fInterval;
		z = -nSubdivide / 2 * fInterval;
		y = 0;
		dVertexData->m_PositionData.push_back(Vector3(x, y, z));
		x = (-nSubdivide / 2 + i) * fInterval;
		z = nSubdivide / 2 * fInterval;
		y = 0;
		dVertexData->m_PositionData.push_back(Vector3(x, y, z));


		x = -nSubdivide / 2 * fInterval;
		y = 0;
		z = (-nSubdivide / 2 + i) * fInterval;
		dVertexData->m_PositionData.push_back(Vector3(x, y, z));
		x = nSubdivide / 2 * fInterval;
		y = 0;
		z = (-nSubdivide / 2 + i) * fInterval;
		dVertexData->m_PositionData.push_back(Vector3(x, y, z));
	}
	dVertexData->m_PrimitiveType = EPRIMITIVE_LINE;
	dVertexData->m_nNumVertex = (nSubdivide + 1) * 4;


	//std::vector<int> vecIndex;
	//IndexData* pIndexData = new IndexData;
	//pSceneGridRenderable->m_pIndexData = pIndexData;
	//int nLineNum = (nSubdivide + 1) * 2;
	//pIndexData->indexNum = nLineNum * 2;
	//for (int i = 0; i < nSubdivide + 1; ++i)
	//{
	//	vecIndex.push_back(i * 4);
	//	vecIndex.push_back(i * 4 + 1);
	//	vecIndex.push_back(i * 4 + 2);
	//	vecIndex.push_back(i * 4 +  3);
	//}

	////
	//if (dVertexData->nNumVertex > 65535)
	//{
	//	pIndexData->indexDesc = EIndexInt;
	//	pIndexData->pData = new int[pIndexData->indexNum];
	//	int* pData = (int*)pIndexData->pData;
	//	for (int i = 0; i < pIndexData->indexNum; ++i)
	//	{
	//		pData[i] = vecIndex[i];
	//		//std::cout <<"index:" << i << " = " << vecIndex[i] << std::endl;
	//	}
	//}
	//else
	//{
	//	pIndexData->indexDesc = EIndexShort;
	//	pIndexData->pData = new unsigned short[pIndexData->indexNum];
	//	unsigned short* pData = (unsigned short*)pIndexData->pData;
	//	for (int i = 0; i < pIndexData->indexNum; ++i)
	//	{
	//		pData[i] = (unsigned short)vecIndex[i];
	//		//std::cout << "index:" << i << " = " << vecIndex[i];// << std::endl;
	//	}
	//	//std::cout << endl;
	//}
}

SmartPointer<IWorldObj> ZG::GizmoManager::BuildSelectObj(SmartPointer<IWorldObj> pSelObj)
{
	SmartPointer<IWorldObj> pSelectObjWireFrame = nullptr;
	pSelectObjWireFrame = pSelObj->Clone(false);
	std::vector<SmartPointer<ModuleBase>> vecModule;
	pSelectObjWireFrame->GetAllModule<ModuleBase>(vecModule);
	for each (SmartPointer<ModuleBase> pModule in vecModule)
	{
		if (dynamic_cast<IRenderable*>(pModule.get()) == nullptr && dynamic_cast<Transform*>(pModule.get()) == nullptr)
		{
			pModule->m_pOwnerObj->removeModule(pModule);
		}

	}
	std::vector<SmartPointer<IRenderable>> vecRend;
	pSelectObjWireFrame->GetAllModule<IRenderable>(vecRend);
	pSelectObjWireFrame->m_pTransform->SetWorldTransform(pSelObj->m_pTransform->GetWorldMatrix());

	for each (SmartPointer<IRenderable> rend in vecRend)
	{
		rend->m_pSharedMaterial = rend->GetDefaultMaterial();
		RasterMaterial* pMat = dynamic_cast<RasterMaterial*>(rend->GetMaterialInstance().get());
		pMat->SetArg<GameColor>("MainColor", GameColor::green);
		if (pMat != nullptr)
		{
			for each (std::pair<std::string, ZG::SmartPointer<ZG::MaterialPass>> p in pMat->m_MaterialPass)
			{
				stRenderState s;
				s.m_eRenderState = FILLMODE;
				s.m_nValue = EFILLMODE_WIREFRAME;
				p.second->SetRenderState(s);
				s.m_eRenderState = ZTEST;
				s.m_nValue = true;
				p.second->SetRenderState(s);
				s.m_eRenderState = ZFUNC;
				s.m_nValue = RENDERCMP_LESSEQUAL;
				p.second->SetRenderState(s);
				//
				p.second->SetRenderState(ZDEPTHBIAS, 16);
				p.second->SetRenderState(ZDEPTHSLOPBIAS, 0);

				//

			}
		}
	}
	return pSelectObjWireFrame;
}

IWorldObj* ZG::GizmoManager::CreateSkeletonGizmo(SkeletonModule* pModule)
{
	IWorldObj* pObj = new IWorldObj;
	pObj->m_strName = "SkeletonGizmo";
	IRenderable* pSkeletonArchi = pObj->addModule<IRenderable>().get();
	pSkeletonArchi->m_strName = "SkeletonGizmo";
	pSkeletonArchi->m_pSharedMaterial = pSkeletonArchi->GetDefaultMaterial();

	pSkeletonArchi->GetMaterialInstance()->SetArg<GameColor>("MainColor", GameColor::green * 1.0f);
	RasterMaterial* mat = (RasterMaterial*)pSkeletonArchi->GetMaterialInstance().get();
	stRenderState s;
	s.m_eRenderState = ZTEST;
	s.m_nValue = 0;
	mat->SetRenderState(s);
	DynamicVertexData* dVertexData = new DynamicVertexData;
	pSkeletonArchi->m_pVertexData = dVertexData;


	int nNumVertex = 0;
	//
	for each (std::pair<int, SkeletonObj*> p in pModule->m_mapSkeletonObj)
	{
		SkeletonObj* pObj = p.second;
		for (int i = 0; i < pObj->GetChildCount(); ++i)
		{
			dVertexData->m_PositionData.push_back(pObj->m_pTransform->GetWorldTranslate());
			dVertexData->m_PositionData.push_back(pObj->GetChild(i)->m_pTransform->GetWorldTranslate());
			nNumVertex += 2;
		}
	}
	dVertexData->m_PrimitiveType = EPRIMITIVE_LINE;
	dVertexData->m_nNumVertex = nNumVertex;
	return pObj;
}

void ZG::GizmoManager::OnAppClose()
{
	////
	//SmartPointer<TranslateGizmo> m_pTranslateGizmo;
	////
	//SmartPointer<IWorldObj>	 m_pSceneGrid;
	////
	//SmartPointer<IWorldObj>	 m_pSelectObjWireFrame;
	m_pTranslateGizmo = nullptr;
	m_pSceneGrid = nullptr;
	//pSelectObjWireFrame = nullptr;
}
