
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
#include "TimeManager.h"
template class EDITOR_API Singleton<EditorApplication>;
template<> shared_ptr<EditorApplication> Singleton<EditorApplication>::_instance = nullptr;

EditorApplication::EditorApplication()
{
}


EditorApplication::~EditorApplication()
{
	int i = m_mapListener.size();


	for each (std::pair<string,std::shared_ptr<IListener>> p in m_mapListener)
	{
		p.second = nullptr;
	}
	int ii = 2;
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
	RenderManager::GetInstance()->GetDefaultRenderSystem()->OnFrameBegin();
	//
	std::vector<std::shared_ptr<RasterCamera>> m_CameraList;
	std::vector<std::shared_ptr<CameraRenderer>> m_CameraIgnoreList;
	//camera will not render
	m_CameraList = EditorApplication::GetInstance()->m_pWorld->GetAllModules<RasterCamera>();
	for each (shared_ptr<CameraBase> pCamera in m_CameraList)
	{
		for each (std::pair<string, std::shared_ptr<IListener>> p in pCamera->m_mapListener)
		{
			std::shared_ptr<CameraRenderer> cameraRender = dynamic_pointer_cast<CameraRenderer>(p.second);
			if (cameraRender->m_pTarget == nullptr)
			{
				cameraRender->m_bActive = false;
			}
		}
	}
	//
	m_pWorld->Update();
	std::map<int, EditorRenderView*>::iterator iter = m_ViewMap.begin();
	for (; iter != m_ViewMap.end(); ++iter)
	{
		iter->second->Update();
	}
	RenderManager::GetInstance()->GetDefaultRenderSystem()->OnFrameEnd();

	//
	TimeManager::GetInstance()->Update();
	//
}
void EditorApplication::SetupScene()
{
	AssetManager::GetInstance()->LoadAsset("./data/prefab/plane.prefab.xml");
	shared_ptr<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->GetResource("./data/prefab/plane.prefab.xml");
	shared_ptr<IWorldObj> pObj = pPrefab->m_pRoot->Clone(true);

	//m_pTargetObj = pObj;
	m_pWorld->m_pRoot->addChild(pObj);






	shared_ptr<IWorldObj> pCamera(IWorldObj::CreateWorldObj());
	pCamera->m_strName = "Camera";
	m_pWorld->m_pRoot->addChild(pCamera);
	shared_ptr<RasterCamera> pCameraModule = pCamera->addModule<RasterCamera>(pCamera);
	pCameraModule->m_fFar = 2000.0f;
	pCameraModule->m_fNear = 3.0f;
	pCameraModule->m_fAspect = (float)m_RenderViewInfo.m_nWidth / m_RenderViewInfo.m_nHeight;
	pCameraModule->m_fFovy = PI / 4;


	std::shared_ptr<CameraRenderer> pCameraRenderer(new CameraRenderer);// = new CameraRenderer;
	pCameraRenderer->m_pWorld = m_pWorld;
	//pCameraRenderer->m_pTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
	pCameraRenderer->m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	pCameraRenderer->m_clrColr = GameColor::white;
	pCameraModule->AddListener("CameraRenderer", pCameraRenderer);

	pCamera->m_pTransform->SetTranslate(Vector3(0.0f, 400.0f, -550.0f));
	pCamera->m_pTransform->SetOrientation(AngleToRad(35.0f), 0, 0);

	shared_ptr<IWorldObj> pLightObj(IWorldObj::CreateWorldObj());
	pLightObj->m_pTransform->SetTranslate(0.0f, 130.0f, 0.0f);
	pLightObj->m_pTransform->SetOrientation(AngleToRad(35.0f), 0.0f, 0.0f);
	pLightObj->m_strName = "Lights";
	shared_ptr<DirectionalLight> pDirLight = pLightObj->addModule<DirectionalLight>(pLightObj);
	pDirLight->m_fIntensity = 1.5f;
	pDirLight->m_Color = GameColor::white;
	m_pWorld->m_pRoot->addChild(pLightObj);


	NotifyListener("InitScene", EditorApplication::GetInstance());

	
}

void EditorApplication::NotifyListener(string msg, std::shared_ptr<IListenerSubject> pSubject)
{
	IListenerSubject::NotifyListener(msg, pSubject);
	m_pEditorApp->OnNotify(msg, pSubject);
}

void EditorApplication::OnSelectChange(shared_ptr<IWorldObj> pObj)
{
	m_SelectObj = pObj;
	NotifyListener("SelectChange", EditorApplication::GetInstance());
}