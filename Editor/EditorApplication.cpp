
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
#include "Sphere3D.h"
#include "Cylinder.h"
#include "Cone.h"
#include "GizmoManager.h"
#include "TranslateGizmo.h"
using namespace ZG;
//#include "FilePath.h"
template class EDITOR_API Singleton<EditorApplication>;
template<> SmartPointer<EditorApplication> Singleton<EditorApplication>::_instance = nullptr;

EditorApplication::EditorApplication()
{
}


EditorApplication::~EditorApplication()
{
	int i = m_mapListener.size();


	for each (std::pair<string,SmartPointer<IListener>> p in m_mapListener)
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
	static bool bout = true;
	if (bout == true)
	{
		std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
		bout = false;
	}
	
	RenderManager::GetInstance()->GetDefaultRenderSystem()->OnFrameBegin();
	//
	std::vector<SmartPointer<RasterCamera>> m_CameraList;
	std::vector<SmartPointer<CameraRenderer>> m_CameraIgnoreList;
	//camera will not render
	m_CameraList = EditorApplication::GetInstance()->m_pWorld->GetAllModules<RasterCamera>();
	for each (SmartPointer<RasterCamera> pCamera in m_CameraList)
	{
		for each (std::pair<string, IListener*> p in pCamera->m_mapListener)
		{
			SmartPointer<CameraRenderer> cameraRender = dynamic_cast<CameraRenderer*>(p.second);
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
	//NotifyListener("SelectChange", EditorApplication::GetInstance());
}
void EditorApplication::SetupScene()
{
	std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
	AssetManager::GetInstance()->LoadAsset("./data/prefab/plane.prefab.xml");
	SmartPointer<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->GetResource("./data/prefab/plane.prefab.xml");
	SmartPointer<IWorldObj> pObj = pPrefab->m_pRoot->Clone(true);

	//m_pTargetObj = pObj;
	m_pWorld->m_pRoot->addChild(pObj);






	SmartPointer<IWorldObj> pCamera(IWorldObj::CreateWorldObj());
	pCamera->m_strName = "Camera";
	m_pWorld->m_pRoot->addChild(pCamera);
	SmartPointer<RasterCamera> pCameraModule = pCamera->addModule<RasterCamera>(pCamera);
	pCameraModule->m_fFar = 12000.0f;
	pCameraModule->m_fNear = 3.0f;
	pCameraModule->m_fAspect = (float)m_RenderViewInfo.m_nWidth / m_RenderViewInfo.m_nHeight;
	pCameraModule->m_fFovy = PI / 4;


	SmartPointer<CameraRenderer> pCameraRenderer(new CameraRenderer);// = new CameraRenderer;
	pCameraRenderer->m_pWorld = m_pWorld.get();
	//pCameraRenderer->m_pTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
	pCameraRenderer->m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	pCameraRenderer->m_clrColr = GameColor::white;
	pCameraModule->AddListener("CameraRenderer", pCameraRenderer.get());

	pCamera->m_pTransform->SetTranslate(Vector3(0.0f, 400.0f, -550.0f));
	pCamera->m_pTransform->SetOrientation(AngleToRad(35.0f), 0, 0);

	SmartPointer<IWorldObj> pLightObj(IWorldObj::CreateWorldObj());
	pLightObj->m_pTransform->SetTranslate(0.0f, 130.0f, 0.0f);
	pLightObj->m_pTransform->SetOrientation(AngleToRad(35.0f), 0.0f, 0.0f);
	pLightObj->m_strName = "Lights";
	SmartPointer<DirectionalLight> pDirLight = pLightObj->addModule<DirectionalLight>(pLightObj);
	pDirLight->m_fIntensity = 1.5f;
	pDirLight->m_Color = GameColor::white;
	m_pWorld->m_pRoot->addChild(pLightObj);


	////sphere
	//SmartPointer<IWorldObj> pSphereObj(IWorldObj::CreateWorldObj());
	//m_pWorld->m_pRoot->addChild(pSphereObj);
	//pSphereObj->m_strName = "Sphere";
	//SmartPointer<Sphere3D> pSphere = pSphereObj->addModule<Sphere3D>(pSphereObj);
	//pSphere->m_fRadius = 50.0f;
	//pSphere->m_nSubdivide = 40;
	//pSphere->GeneratePolygon();
	//pSphereObj->m_pTransform->SetTranslate(110.0, 150, 0.0);

	////cyilnder
	//SmartPointer<IWorldObj> pCylinderObj(IWorldObj::CreateWorldObj());
	//m_pWorld->m_pRoot->addChild(pCylinderObj);
	//pCylinderObj->m_strName = "Cylinder";
	//SmartPointer<Cylinder> pCylinder = pSphereObj->addModule<Cylinder>(pCylinderObj);
	//pCylinder->m_fRadius = 25.0f;
	//pCylinder->m_fHeight = 100.0f;
	//pCylinder->m_nSubdivide = 40;
	//pCylinder->GeneratePolygon();
	//pCylinderObj->m_pTransform->SetTranslate(0.0, 150, 0.0);
	////
	//SmartPointer<IWorldObj> pConeObj(IWorldObj::CreateWorldObj());
	//m_pWorld->m_pRoot->addChild(pConeObj);
	//pConeObj->m_strName = "Cone";
	//SmartPointer<Cone> pCone = pSphereObj->addModule<Cone>(pConeObj);
	//pCone->m_fRadius = 25.0f;
	//pCone->m_fHeight = 100.0f;
	//pCone->m_nSubdivide = 40;
	//pCone->GeneratePolygon();
	//pConeObj->m_pTransform->SetTranslate(-100.0, 150, 0.0);
	//
	m_pWorld->m_pRoot->addChild(GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot);
	GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetTranslate(0.0f, 150.0f, 0.0f);
	GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetScale(2, 2, 2);


	NotifyListener("InitScene", EditorApplication::GetInstance());
}

void EditorApplication::NotifyListener(string msg, IListenerSubject* pSubject)
{
	IListenerSubject::NotifyListener(msg, pSubject);
	m_pEditorApp->OnNotify(msg, pSubject);
}

void EditorApplication::OnSelectChange(SmartPointer<IWorldObj> pObj)
{
	m_SelectObj = pObj;
	NotifyListener("SelectChange", EditorApplication::GetInstance());
}

void EditorApplication::OnInit()
{
	if (false == GizmoManager::GetInstance()->Init())
	{

	}
}
