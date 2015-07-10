
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
#include "Ring.h"
#include "IListener.h"
#include "Skeleton.h"
#include "SceneResource.h"
#include "SingleResourceAsset.h"
#include "EditorCommands.h"
#include "SkeletonResource.h"
#include "EditorEvents.h"
#include "EditorSceneView.h"
#include "EditorCommandManager.h"
using namespace ZG;
//#include "FilePath.h"
template class EDITOR_API Singleton<EditorApplication>;
template<> SmartPointer<EditorApplication> Singleton<EditorApplication>::_instance = nullptr;

EditorApplication::EditorApplication()
	:m_eOperState(EditorApplication::EStateTranslate)
	, m_eSelState(ESelNone)
	, m_pGizmoScene(nullptr)
	, m_bShowSkeletonGizmo(false)
{
	addEvent("ADDTOSCENEGGRAPH", new Event<AddSceneGraphEventArg>());
	addEvent("DELETEFROMSCENEGRAPH", new Event<DeleteSceneGraphEventArg>());
	addEvent("SCENEGRAPHSELCHANGE", new Event<SceneGraphSelChangeArg>());
	addEvent("EDITORUPDATE", new Event<EditorUpdateArg>());

}


EditorApplication::~EditorApplication()
{
	int i = m_mapListener.size();


	for each (std::pair<string, IListener*> p in m_mapListener)
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
	//return;
	RenderManager::GetInstance()->GetDefaultRenderSystem()->OnFrameBegin();
	//std::cout << "frame begin end" << std::endl;
	//
	std::vector<SmartPointer<RasterCamera>> m_CameraList;
	//camera will not render
	m_CameraList = EditorApplication::GetInstance()->m_pWorld->GetAllModules<RasterCamera>();
	for each (SmartPointer<RasterCamera> pCamera in m_CameraList)
	{
		if (pCamera->m_pTarget == nullptr || pCamera->m_pTarget == RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView())
		{
			pCamera->SetActive(false);
		}
	}
	
	//
	m_pWorld->Update();
	UpdateGizemo();
	m_pGizmoScene->Update();
	std::map<int, EditorRenderView*>::iterator iter = m_ViewMap.begin();
	//std::cout << "update start" << std::endl;
	for (; iter != m_ViewMap.end(); ++iter)
	{
		iter->second->Update();
	}
	//std::cout << "update end" << std::endl;
	RenderManager::GetInstance()->GetDefaultRenderSystem()->OnFrameEnd();

	EditorUpdateArg updateArg;
	(*getEvent<EditorUpdateArg>("EDITORUPDATE"))(updateArg);
	//
	TimeManager::GetInstance()->Update();
	//
	//NotifyListener("SelectChange", EditorApplication::GetInstance());
}
void EditorApplication::SetupScene()
{

	//std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
	AssetManager::GetInstance()->LoadAsset("./data/prefab/plane.prefab.xml");
	SmartPointer<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->GetResource("./data/prefab/plane.prefab.xml");
	SmartPointer<IWorldObj> pObj = pPrefab->m_pRoot->Clone(true);

	//m_pTargetObj = pObj;
	m_pWorld->m_pRoot->addChild(pObj);






	SmartPointer<IWorldObj> pCamera(new IWorldObj);
	pCamera->m_strName = "Camera";
	m_pWorld->m_pRoot->addChild(pCamera);
	SmartPointer<RasterCamera> pCameraModule = pCamera->addModule<RasterCamera>();
	pCameraModule->m_fFar = 12000.0f;
	pCameraModule->m_fNear = 10.0f;
	pCameraModule->m_fAspect = (float)m_RenderViewInfo.m_nWidth / m_RenderViewInfo.m_nHeight;
	pCameraModule->m_fFovy = PI / 4;

	pCameraModule->m_pWorld = m_pWorld.get();
	pCameraModule->m_pTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
	pCameraModule->m_clrColr = GameColor::white;
	RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender()->RegistCamera(pCameraModule.get());
	//pCameraModule->getEvent<CameraRenderEvent>("CAMERARENDER")->addEventHandler(RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender(), std::bind(&(IRender::OnCameraRender), RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender(), std::placeholders::_1));


	//CameraRenderer* pCameraRenderer = new CameraRenderer;
	//pCameraRenderer->m_pWorld = m_pWorld.get();
	////pCameraRenderer->m_pTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
	//pCameraRenderer->m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	//pCameraRenderer->m_clrColr = GameColor::white;
	//pCameraModule->AddListener("CameraRenderer", pCameraRenderer);

	pCamera->m_pTransform->SetTranslate(Vector3(0.0f, 400.0f, -550.0f));
	pCamera->m_pTransform->SetOrientation(AngleToRad(35.0f), 0, 0);

	SmartPointer<IWorldObj> pLightObj(new IWorldObj);
	pLightObj->m_pTransform->SetTranslate(0.0f, 130.0f, 0.0f);
	pLightObj->m_pTransform->SetOrientation(AngleToRad(35.0f), 0.0f, 0.0f);
	pLightObj->m_strName = "Lights";
	SmartPointer<DirectionalLight> pDirLight = pLightObj->addModule<DirectionalLight>();
	pDirLight->m_fIntensity = 1.0f;
	pDirLight->m_Color = GameColor::white;
	m_pWorld->m_pRoot->addChild(pLightObj);
	//ring
	//SmartPointer<IWorldObj> pRingObj(new IWorldObj);
	//m_pWorld->m_pRoot->addChild(pRingObj);
	//pRingObj->m_strName = "Ring";
	//SmartPointer<Ring> pRing = pRingObj->addModule<Ring>();
	//pRing->GeneratePolygon();
	//pRingObj->m_pTransform->SetTranslate(0.0f, 150.0f, 0.0f);



	////sphere
	//SmartPointer<IWorldObj> pSphereObj(new IWorldObj);
	//m_pWorld->m_pRoot->addChild(pSphereObj);
	//pSphereObj->m_strName = "Sphere";
	//SmartPointer<Sphere3D> pSphere = pSphereObj->addModule<Sphere3D>(pSphereObj);
	//pSphere->m_fRadius = 50.0f;
	//pSphere->m_nSubdivide = 40;
	//pSphere->GeneratePolygon();
	//pSphereObj->m_pTransform->SetTranslate(110.0, 150, 0.0);

	////cyilnder
	//SmartPointer<IWorldObj> pCylinderObj(new IWorldObj);
	//m_pWorld->m_pRoot->addChild(pCylinderObj);
	//pCylinderObj->m_strName = "Cylinder";
	//SmartPointer<Cylinder> pCylinder = pSphereObj->addModule<Cylinder>(pCylinderObj);
	//pCylinder->m_fRadius = 25.0f;
	//pCylinder->m_fHeight = 100.0f;
	//pCylinder->m_nSubdivide = 40;
	//pCylinder->GeneratePolygon();
	//pCylinderObj->m_pTransform->SetTranslate(0.0, 150, 0.0);
	////
	//SmartPointer<IWorldObj> pConeObj(new IWorldObj);
	//m_pWorld->m_pRoot->addChild(pConeObj);
	//pConeObj->m_strName = "Cone";
	//SmartPointer<Cone> pCone = pSphereObj->addModule<Cone>(pConeObj);
	//pCone->m_fRadius = 25.0f;
	//pCone->m_fHeight = 100.0f;
	//pCone->m_nSubdivide = 40;
	//pCone->GeneratePolygon();
	//pConeObj->m_pTransform->SetTranslate(-100.0, 150, 0.0);
	//
	//m_pWorld->m_pRoot->addChild(GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot);
	//GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetTranslate(0.0f, 150.0f, 0.0f);
	//GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetScale(2, 2, 2);

	//
	m_pWorld->addEvent("PRESCENERENDER", new Event<IWorld>());
	m_pWorld->addEvent("POSTSCENERENDER", new Event<IWorld>());
	m_pGizmoScene = new IWorld;
	m_pGizmoScene->m_pRoot->addChild(GizmoManager::GetInstance()->m_pSceneGrid);
	//m_pWorld->m_pRoot->addChild(GizmoManager::GetInstance()->m_pSceneGrid);
	NotifyListener("InitScene", EditorApplication::GetInstance());
	//SelectChange(nullptr);
}

void EditorApplication::NotifyListener(string msg, IListenerSubject* pSubject)
{
	IListenerSubject::NotifyListener(msg, pSubject);
	m_pEditorApp->OnNotify(msg, pSubject);
}

void EditorApplication::SelectChange(SmartPointer<IWorldObj> pObj)
{

	if (m_vecSelectObjs.size() == 1 && m_vecSelectObjs[0] == pObj)
	{
		return;
	}
	m_vecSelectObjs.clear();
	if (pObj != nullptr)
	{
		m_vecSelectObjs.push_back(pObj);
	}
	NotifySelectionChange();
}

void EditorApplication::OnInit()
{
	if (false == GizmoManager::GetInstance()->Init())
	{
		std::cout << "gizmo init failed!" << std::endl;
	}
}

void ZG::EditorApplication::UpdateGizemo()
{
	
	m_pGizmoScene->m_pRoot->removeAllChildren();
	m_pGizmoScene->m_pRoot->addChild(GizmoManager::GetInstance()->m_pSceneGrid);
	if (getSelectObj() != nullptr)
	{
		switch (m_eOperState)
		{
			case ZG::EditorApplication::EStateSelect:
			{
				
			}
			break;
			case ZG::EditorApplication::EStateTranslate:
			{
				m_pGizmoScene->m_pRoot->addChild(GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot);
				//GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetTranslate(m_SelectObj->m_pTransform->GetWorldTranslate());
			}
			break;
			case ZG::EditorApplication::EStateRotate:
			{

			}
			break;
			case ZG::EditorApplication::EStateScale:
			{

			}
			break;
			default:
			break;
		}
	}
	for each (SmartPointer<IWorldObj> pObj in m_vecSelectObjs)
	{
		SmartPointer<IWorldObj> pCloneObj = GizmoManager::GetInstance()->BuildSelectObj(pObj);
		m_pGizmoScene->m_pRoot->addChild(pCloneObj);
	}
	if (m_bShowSkeletonGizmo == true || true)
	{
		std::vector<SmartPointer<SkeletonModule>> vecSkeleton;
		m_pWorld->m_pRoot->GetAllModuleRecursive<SkeletonModule>(vecSkeleton);
		for each (SmartPointer<SkeletonModule> pSkeletonModule in vecSkeleton)
		{
			IWorldObj* pObj = GizmoManager::GetInstance()->CreateSkeletonGizmo(pSkeletonModule.get());
			m_pGizmoScene->m_pRoot->addChild(pObj);
		}
	}

	

}

void ZG::EditorApplication::OnClickScene(SmartPointer<CameraBase> pCamera, SmartPointer<RenderView> pRenderView)
{

}

void ZG::EditorApplication::SaveScene(std::string fileName)
{
	SceneResource* pRes = ResourceManager<SceneResource>::GetInstance()->CreateResource<SceneResource>(fileName).get();
	pRes->m_pRoot = m_pWorld->m_pRoot;
	SingleResourceAsset* pAsset = new SingleResourceAsset;
	pAsset->AddResource(fileName, pRes);
	pAsset->m_strPath = fileName;
	AssetManager::GetInstance()->Save(pAsset);


	//ResourceManager<SceneResource>::GetInstance()->RemoveResource(fileName);

	AssetManager::GetInstance()->ReleaseAsset(pAsset->m_strPath,true);
}

void ZG::EditorApplication::LoadScene(std::string fileName)
{
	IAsset* pAsset = AssetManager::GetInstance()->LoadAsset(fileName);
	if (pAsset == nullptr)
	{
		return;
	}
	SceneResource* pRes = pAsset->GetResource<SceneResource>();
	if (pRes == nullptr)
	{
		AssetManager::GetInstance()->ReleaseAsset(fileName, true);
		return;
	}
	m_pWorld->m_pRoot = pRes->m_pRoot;

	AssetManager::GetInstance()->ReleaseAsset(fileName, true);
	NotifyListener("InitScene", EditorApplication::GetInstance());
}

bool ZG::EditorApplication::excuteCommond(ICommand* pCommand)
{
	DeleteCommand* pDeleteCmd = dynamic_cast<DeleteCommand*>(pCommand);
	if (pDeleteCmd != nullptr)
	{
		DeleteSceneGraphEventArg arg;
		arg.m_pObj = pDeleteCmd->m_pObj.get();
		arg.m_pParent = pDeleteCmd->m_pParentObj.get();
		//
		pDeleteCmd->m_pParentObj->removeChild(pDeleteCmd->m_pObj);
		SelectChange(nullptr);
		//NotifyListener("InitScene", EditorApplication::GetInstance());
		//

		(*getEvent < DeleteSceneGraphEventArg >("DELETEFROMSCENEGRAPH"))(arg);
		EditorApplication::GetInstance()->SelectChange(nullptr);
		return true;
	}
	AddToSceneCommand* pAddToSceneCmd = dynamic_cast<AddToSceneCommand*>(pCommand);
	if (pAddToSceneCmd != nullptr)
	{
		pAddToSceneCmd->m_pParentObj->addChild(pAddToSceneCmd->m_pObj);
		//EditorApplication::GetInstance()->NotifyListener("InitScene", EditorApplication::GetInstance());

		AddSceneGraphEventArg arg;
		arg.m_pObj = pAddToSceneCmd->m_pObj.get();
		arg.m_pParent = pAddToSceneCmd->m_pParentObj.get();
		(*getEvent < AddSceneGraphEventArg >("ADDTOSCENEGGRAPH"))(arg);
		EditorApplication::GetInstance()->SelectChange(arg.m_pObj);
		return true;
	}
	MoveCommand* pMovCmd = dynamic_cast<MoveCommand*>(pCommand);
	if (pMovCmd != nullptr)
	{
		pMovCmd->m_pObj->m_pTransform->SetWorldTranslate(pMovCmd->m_vecNextPos);
		return true;
	}
	return false;
}

bool ZG::EditorApplication::undoCommond(ICommand* pCommand)
{
	DeleteCommand* pDeleteCmd = dynamic_cast<DeleteCommand*>(pCommand);
	if (pDeleteCmd != nullptr)
	{
		if (pDeleteCmd->m_pObj->GetParent() != nullptr)
		{
			pDeleteCmd->m_pObj->GetParent()->removeChild(pDeleteCmd->m_pObj);
		}
		pDeleteCmd->m_pParentObj->addChild(pDeleteCmd->m_pObj);
		//NotifyListener("InitScene", EditorApplication::GetInstance());
		//
		AddSceneGraphEventArg arg;
		arg.m_pObj = pDeleteCmd->m_pObj.get();
		arg.m_pParent = pDeleteCmd->m_pParentObj.get();
		(*getEvent < AddSceneGraphEventArg >("ADDTOSCENEGGRAPH"))(arg);
		SelectChange(pDeleteCmd->m_pObj);
		return true;
	}
	AddToSceneCommand* pAddToSceneCmd = dynamic_cast<AddToSceneCommand*>(pCommand);
	if (pAddToSceneCmd != nullptr)
	{
		DeleteSceneGraphEventArg arg;
		arg.m_pObj = pAddToSceneCmd->m_pObj.get();
		arg.m_pParent = pAddToSceneCmd->m_pParentObj.get();
		//
		pAddToSceneCmd->m_pParentObj->removeChild(pAddToSceneCmd->m_pObj);
		//
		(*getEvent < DeleteSceneGraphEventArg >("DELETEFROMSCENEGRAPH"))(arg);
		EditorApplication::GetInstance()->SelectChange(nullptr);
		return true;
	}
	MoveCommand* pMovCmd = dynamic_cast<MoveCommand*>(pCommand);
	if (pMovCmd != nullptr)
	{
		pMovCmd->m_pObj->m_pTransform->SetWorldTranslate(pMovCmd->m_vecPrePos);
		return true;
	}
	return false;
}

bool ZG::EditorApplication::redoCommond(ICommand* pCommand)
{
	DeleteCommand* pDeleteCmd = dynamic_cast<DeleteCommand*>(pCommand);
	if (pDeleteCmd != nullptr)
	{
		pDeleteCmd->m_pParentObj->removeChild(pDeleteCmd->m_pObj);
		SelectChange(nullptr);

		//
		DeleteSceneGraphEventArg arg;
		arg.m_pObj = pDeleteCmd->m_pObj.get();
		arg.m_pParent = pDeleteCmd->m_pParentObj.get();
		(*getEvent < DeleteSceneGraphEventArg >("DELETEFROMSCENEGRAPH"))(arg);
		EditorApplication::GetInstance()->SelectChange(nullptr);
		//sNotifyListener("InitScene", EditorApplication::GetInstance());
		return true;
	}
	AddToSceneCommand* pAddToSceneCmd = dynamic_cast<AddToSceneCommand*>(pCommand);
	if (pAddToSceneCmd != nullptr)
	{
		pAddToSceneCmd->m_pParentObj->addChild(pAddToSceneCmd->m_pObj);
		//EditorApplication::GetInstance()->NotifyListener("InitScene", EditorApplication::GetInstance());

		//
		AddSceneGraphEventArg arg;
		arg.m_pObj = pAddToSceneCmd->m_pObj.get();
		arg.m_pParent = pAddToSceneCmd->m_pParentObj.get();
		(*getEvent < AddSceneGraphEventArg >("ADDTOSCENEGGRAPH"))(arg);
		EditorApplication::GetInstance()->SelectChange(arg.m_pObj);
		return true;
	}
	MoveCommand* pMovCmd = dynamic_cast<MoveCommand*>(pCommand);
	if (pMovCmd != nullptr)
	{
		pMovCmd->m_pObj->m_pTransform->SetWorldTranslate(pMovCmd->m_vecNextPos);
		return true;
	}
	return false;
}

void ZG::EditorApplication::SetWindowID(int id)
{
	m_RenderViewInfo.m_windowID = id;
	m_nWindowID = id;
}

IWorldObj* ZG::EditorApplication::getSelectObj()
{
	if (m_vecSelectObjs.size() == 0)
	{
		return nullptr;
	}
	return m_vecSelectObjs[0].get();
}

EditorSceneView* ZG::EditorApplication::getActiveScene()
{
	for each (std::pair<int, EditorRenderView*> var in m_ViewMap)
	{
		EditorSceneView* pSceneView = dynamic_cast<EditorSceneView*>(var.second);
		if (pSceneView != nullptr && pSceneView->m_bShow)
		{
			return pSceneView;
		}
	}
	return nullptr;
}

void ZG::EditorApplication::OnClose()
{
	ApplicationBase::OnClose();
	m_pGizmoScene = nullptr;
}

void ZG::EditorApplication::StartTranslate()
{
	m_EditorState.m_vecPressPos = getSelectObj()->m_pTransform->GetWorldTranslate();
	switch (m_eSelState)
	{
		case ZG::EditorApplication::ESelNone:
		break;
		case ZG::EditorApplication::ETranslateRight:
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRightMaterialCone->SetArg<GameColor>("MainColor", GameColor::blue * 1.0f);
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRightMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::blue * 1.0f);
		break;
		case ZG::EditorApplication::ETranslateUp:
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pUpMaterialCone->SetArg<GameColor>("MainColor", GameColor::red * 1.0f);
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pUpMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::red * 1.0f);
		break;
		case ZG::EditorApplication::ETranslateForward:
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pForwardMaterialCone->SetArg<GameColor>("MainColor", GameColor::green * 1.0f);
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pForwardMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::green * 1.0f);
		break;
		default:
		break;
	}
}

void ZG::EditorApplication::EndTranslate()
{

	if (m_eSelState == EditorApplication::ESelNone)
	{
		return;
	}
	switch (m_eSelState)
	{
		case ZG::EditorApplication::ESelNone:
		break;
		case ZG::EditorApplication::ETranslateRight:
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRightMaterialCone->SetArg<GameColor>("MainColor", GameColor::blue * 0.5f);
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRightMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::blue * 0.5f);
		break;
		case ZG::EditorApplication::ETranslateUp:
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pUpMaterialCone->SetArg<GameColor>("MainColor", GameColor::red * 0.5f);
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pUpMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::red * 0.5f);
		break;
		case ZG::EditorApplication::ETranslateForward:
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pForwardMaterialCone->SetArg<GameColor>("MainColor", GameColor::green * 0.5f);
		GizmoManager::GetInstance()->m_pTranslateGizmo->m_pForwardMaterialCylinder->SetArg<GameColor>("MainColor", GameColor::green * 0.5f);
		break;
		default:
		break;
	}
	EditorApplication::GetInstance()->m_eSelState = EditorApplication::ESelNone;
	MoveCommand* pMoveCmd = new MoveCommand;
	pMoveCmd->m_pObj = getSelectObj();
	pMoveCmd->m_vecPrePos = m_EditorState.m_vecPressPos;
	pMoveCmd->m_vecNextPos = getSelectObj()->m_pTransform->GetWorldTranslate();
	pMoveCmd->m_pReceiver = this;
	//
	EditorCommandManager::GetInstance()->ExcuteNewCmd(pMoveCmd);


}
void ZG::EditorApplication::RemoveSelection(IWorldObj* pObj)
{
	std::vector<SmartPointer<IWorldObj>>::iterator iter = m_vecSelectObjs.begin();
	for (; iter != m_vecSelectObjs.end(); ++iter)
	{
		if (iter->get() == pObj)
		{
			m_vecSelectObjs.erase(iter);
			break;
		}
	}
	//
	NotifySelectionChange();
}

void ZG::EditorApplication::AddSelection(IWorldObj* pObj)
{
	for each (SmartPointer<IWorldObj> p in m_vecSelectObjs)
	{
		if (p == pObj)
		{
			return;
		}
	}
	m_vecSelectObjs.push_back(pObj);
	NotifySelectionChange();

}

void ZG::EditorApplication::ClearSelection()
{
	m_SelectObj = nullptr;
	m_vecSelectObjs.clear();
	NotifySelectionChange();
}

void ZG::EditorApplication::NotifySelectionChange()
{
	NotifyListener("SelectChange", EditorApplication::GetInstance());

	SceneGraphSelChangeArg arg;
	for each (SmartPointer<IWorldObj> p in m_vecSelectObjs)
	{
		arg.m_vecObjs.push_back(p.get());
	}
	(*getEvent < SceneGraphSelChangeArg >("SCENEGRAPHSELCHANGE"))(arg);
}

ZG::Vector3 ZG::EditorApplication::GetSelectionsWorldTranslate()
{
	if (m_vecSelectObjs.size() == 0.0f)
	{
		return Vector3::ZERO;
	}
	//
	Vector3 rt = Vector3::ZERO;
	for each (SmartPointer<IWorldObj> pObj in m_vecSelectObjs)
	{
		rt = rt + pObj->m_pTransform->GetWorldTranslate();
	}
	rt = rt * (1.0f / m_vecSelectObjs.size());
	return rt;
}

unsigned int ZG::EditorApplication::GetSelectionCount()
{
	return m_vecSelectObjs.size();
}

IWorldObj* ZG::EditorApplication::GetSelectionByIndex(int index)
{
	if (m_vecSelectObjs.size() <= index)
	{
		return nullptr;
	}
	return m_vecSelectObjs[index].get();
}

