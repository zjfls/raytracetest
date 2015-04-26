
#include "stdafx.h"
#include "EditorApplication.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "RasterRender.h"
#include "RenderView.h"
#include "EditorRenderView.h"
#include "Color.h"
#include "AssetManager.h"
#include "IWorld.h"
#include "IWorldObj.h"
#include "CameraRenderer.h"
#include "PrefabResource.h"
#include "ResourceManager.h"
#include "RasterCamera.h"
#include "DirectionalLight.h"
#include "MathDefine.h"
#include "MathFunc.h"
#include "Vector3.h"
template<> shared_ptr<EditorApplication> Singleton<EditorApplication>::_instance = nullptr;

EditorApplication::EditorApplication()
{
}


EditorApplication::~EditorApplication()
{
}

bool EditorApplication::AddView(int id, EditorRenderView* pView)
{
	if (m_ViewMap.find(id) != m_ViewMap.end())
	{
		return false;
	}
	m_ViewMap[id] = pView;
	return true;
}

bool EditorApplication::RemoveView(int id)
{
	std::map<int, EditorRenderView*>::iterator iter = m_ViewMap.find(id);
	if (iter == m_ViewMap.end())
	{
		return false;
	}
	m_ViewMap.erase(iter);
	return true;
}

void EditorApplication::Run()
{
	
	std::map<int, EditorRenderView*>::iterator iter = m_ViewMap.begin();
	for (; iter != m_ViewMap.end(); ++iter)
	{
		RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender()->SetRenderTarget(0, iter->second->m_pRenderView);
	//	RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender()->ClearTarget(true, GameColor(0.0f,0.0f,1.0f,0.0f), true, 1.0f);
		RenderManager::GetInstance()->GetDefaultRenderSystem()->SetActiveRenderView(iter->second->m_pRenderView);
		m_pWorld->Update();
		iter->second->m_pRenderView->Present();
	}
}
void EditorApplication::SetupScene()
{
	AssetManager::GetInstance()->LoadAsset("./data/prefab/plane.prefab.xml");
	shared_ptr<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->GetResource("./data/prefab/plane.prefab.xml");
	IWorldObj* pObj = pPrefab->m_pRoot->Clone(true);

	//m_pTargetObj = pObj;
	m_pWorld->m_pRoot->addChild(pObj);






	IWorldObj* pCamera = new IWorldObj;
	m_pWorld->m_pRoot->addChild(pCamera);
	RasterCamera* pCameraModule = pCamera->addModule<RasterCamera>();
	pCameraModule->m_fFar = 2000.0f;
	pCameraModule->m_fNear = 3.0f;
	pCameraModule->m_fAspect = (float)m_RenderViewInfo.m_nWidth / m_RenderViewInfo.m_nHeight;
	pCameraModule->m_fFovy = PI / 4;


	CameraRenderer* pCameraRenderer = new CameraRenderer;
	pCameraRenderer->m_pWorld = m_pWorld;
	pCameraRenderer->m_pTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
	pCameraRenderer->m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	pCameraRenderer->m_clrColr = GameColor::black;
	pCameraModule->AddListener("CameraRenderer", pCameraRenderer);

	pCamera->m_pTransform->SetTranslate(Vector3(0.0f, 400.0f, -550.0f));
	pCamera->m_pTransform->SetOrientation(AngleToRad(35.0f), 0, 0);

	IWorldObj* pLightObj = new IWorldObj;
	pLightObj->m_pTransform->SetTranslate(0.0f, 130.0f, 0.0f);
	pLightObj->m_pTransform->SetOrientation(AngleToRad(35.0f), 0.0f, 0.0f);
	pLightObj->m_strName = "Lights";
	DirectionalLight* pDirLight = pLightObj->addModule<DirectionalLight>();
	pDirLight->m_fIntensity = 1.5f;
	pDirLight->m_Color = GameColor::white;

	//PointLight* pLight = pLightObj->addModule<PointLight>();
	//pLight->m_fIntensity =  0.6f;
	//pLight->m_Color = Color::white;
	m_pWorld->m_pRoot->addChild(pLightObj);
}