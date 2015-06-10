#include "stdafx.h"
#include "EditorSceneView.h"
#include "IWorldObj.h"
#include "RasterCamera.h"
#include "MathDefine.h"
#include "EditorApplication.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "MathFunc.h"
#include "IOManager.h"
#include "TimeManager.h"
#include "PickUtil.h"
#include "PrefabResource.h"
#include "AssetManager.h"
#include "FilePath.h"
#include "RasterCamera.h"
#include "RenderManager.h"
#include "IOManager.h"
#include "IOInterface.h"
#include "IRender.h"
#include "RasterRender.h"
#include "IWorld.h"
EditorSceneView::EditorSceneView()
{
	//
	m_pCamera = SmartPointer<IWorldObj>(new IWorldObj);
	m_pCamera->m_strName = "EditorSceneCamera";

	SmartPointer<RasterCamera> pCameraModule = m_pCamera->addModule<RasterCamera>();
	pCameraModule->m_fFar = 12000.0f;
	pCameraModule->m_fNear = 3.0f;
	pCameraModule->m_fAspect = 1 / 1;
	pCameraModule->m_fFovy = PI / 4;
	//

	//CameraRenderer* pCameraRenderer = new CameraRenderer;
	//pCameraRenderer->m_pWorld = EditorApplication::GetInstance()->m_pWorld.get();
	//pCameraRenderer->m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	//pCameraRenderer->m_clrColr = GameColor::blue;
	//pCameraModule->AddListener("CameraRenderer", pCameraRenderer);
	pCameraModule->m_pWorld = EditorApplication::GetInstance()->m_pWorld;
	pCameraModule->m_clrColr = GameColor::white * 0.1f;
	//pCameraModule->m_pTarget = m_pRenderView;
	m_pCameraModule = pCameraModule.get();
	RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender()->RegistCamera(pCameraModule.get());
	//
	m_pCamera->m_pTransform->SetTranslate(Vector3(0.0f, 400.0f, -550.0f));
	m_pCamera->m_pTransform->SetOrientation(AngleToRad(35.0f), 0, 0);
	//
	//
}


EditorSceneView::~EditorSceneView()
{
	//
}

void EditorSceneView::Update()
{
	RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender()->SetRenderTarget(0, m_pRenderView);
	RenderManager::GetInstance()->GetDefaultRenderSystem()->SetActiveRenderView(m_pRenderView);


	if (m_bIsFocus)
	{
		UpdateCamera();
	}


	if (m_bShow == false)
	{
		return;
	}
	//
	m_pCamera->Update();
	m_pCamera->AfterUpdate();
	//
	DrawGizmo();
	//
	m_pRenderView->Present();
}

void EditorSceneView::Resize(unsigned int nWidth, unsigned int nHeight)
{
	SmartPointer<RasterCamera> pCameraModule = m_pCamera->GetModule(1).SmartPointerCast<RasterCamera>();
	pCameraModule->m_fAspect = float(nWidth) / nHeight;
	EditorRenderView::Resize(nWidth, nHeight);
}

void EditorSceneView::OnMouseWheel(short zDelta, Vector2& pt)
{
	Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
	Vector3 dir = m_pCamera->m_pTransform->GetForward();
	dir = dir.normalize();
	//
	position += zDelta * 0.2 * dir;
	m_pCamera->m_pTransform->SetTranslate(position);
	//
}

void EditorSceneView::OnMouseMove(Vector2& pt)
{
	if (IOManager::GetInstance()->m_pIO->IsRBDown() == true)
	{
		Vector2 diff = pt - m_LastMousePos;
		//std::cout << "mouse move with rb down "<<"x:"<<pt.m_fx<<"y:"<<pt.m_fy << std::endl;
		Orientation rot = m_pCamera->m_pTransform->GetOrientation();
		Vector3 vecRot = rot.m_vecEulerAngle;
		vecRot.m_fy = vecRot.m_fy + (diff.m_fx) * 0.0004;
		vecRot.m_fx = vecRot.m_fx + (diff.m_fy) * 0.0004;
		m_pCamera->m_pTransform->SetOrientation(vecRot.m_fx,vecRot.m_fy,vecRot.m_fz);


		m_LastMousePos = pt;
	}
}

void EditorSceneView::OnMouseLButtonDown(Vector2& pt)
{

}

void EditorSceneView::OnMouseRButtonDown(Vector2& pt)
{
	m_LastMousePos = pt;
}

void EditorSceneView::OnKeyPressed(int key)
{

}

void EditorSceneView::OnDragEnter(Vector2& pos, std::string file)
{

}

void EditorSceneView::OnDrop(Vector2& pos, std::string path)
{
	std::string filesuffix = getFileSuffix(path);
	if (filesuffix == "prefab.xml")
	{
		SmartPointer<CameraBase> pCameraModule = m_pCamera->GetModule(1).SmartPointerCast<CameraBase>();
		Vector3 worldPos = PickUtil::ScreenPosToWorldPos(pos, 500, pCameraModule, m_pRenderView->m_nWidth, m_pRenderView->m_nHeight);
		const char* strPath = path.c_str() + 8;


		AssetManager::GetInstance()->LoadAsset(strPath);
		SmartPointer<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->GetResource(strPath);
		SmartPointer<IWorldObj> pObj = pPrefab->m_pRoot->Clone(true);



		//m_pTargetObj = pObj;
		EditorApplication::GetInstance()->m_pWorld->m_pRoot->addChild(pObj);
		pObj->m_pTransform->SetTranslate(worldPos);

		EditorApplication::GetInstance()->NotifyListener("InitScene", EditorApplication::GetInstance());
	}

	
}

void EditorSceneView::Create(unsigned int nWidth, unsigned int nHeight, int windowID)
{
	EditorRenderView::Create(nWidth, nHeight, windowID);
	m_pCameraModule->m_pTarget = m_pRenderView;
}

void EditorSceneView::UpdateCamera()
{
	SmartPointer<IOInterface> pInterface = IOManager::GetInstance()->m_pIO;
	if (pInterface->IsKeyDown('W') == true)
	{

		Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
		Vector3 dir = m_pCamera->m_pTransform->GetForward();
		dir = dir.normalize();
		//
		Vector3 diff = 2000 * TimeManager::GetInstance()->m_fElapseTime * dir;
		std::cout << "move front:" << "x:" << diff.m_fx << "y:" << diff.m_fy << "z:" << diff.m_fz << "ElapseTime:" << TimeManager::GetInstance()->m_fElapseTime << std::endl;
		position += diff;
		m_pCamera->m_pTransform->SetTranslate(position);
	}
	if (pInterface->IsKeyDown('S') == true)
	{
		Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
		Vector3 dir = m_pCamera->m_pTransform->GetForward();
		dir = dir.normalize();
		//
		Vector3 diff = 2000 * TimeManager::GetInstance()->m_fElapseTime * dir;
		position = position - diff;
		m_pCamera->m_pTransform->SetTranslate(position);
	}
	if (pInterface->IsKeyDown('A') == true)
	{
		Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
		Vector3 dir = -m_pCamera->m_pTransform->GetRight();
		dir = dir.normalize();
		//
		Vector3 diff = 2000 * TimeManager::GetInstance()->m_fElapseTime * dir;
		std::cout << "move front:" << "x:" << diff.m_fx << "y:" << diff.m_fy << "z:" << diff.m_fz << "ElapseTime:" << TimeManager::GetInstance()->m_fElapseTime << std::endl;
		position += diff;
		m_pCamera->m_pTransform->SetTranslate(position);
	}
	if (pInterface->IsKeyDown('D') == true)
	{
		Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
		Vector3 dir = m_pCamera->m_pTransform->GetRight();
		dir = dir.normalize();
		//
		Vector3 diff = 2000 * TimeManager::GetInstance()->m_fElapseTime * dir;
		std::cout << "move front:" << "x:" << diff.m_fx << "y:" << diff.m_fy << "z:" << diff.m_fz << "ElapseTime:" << TimeManager::GetInstance()->m_fElapseTime << std::endl;
		position += diff;
		m_pCamera->m_pTransform->SetTranslate(position);
	}
}

void EditorSceneView::OnClick(Vector2& pos)
{

}

void EditorSceneView::DrawGizmo()
{
	bool bCameraHDR = m_pCameraModule->m_bHDR;
	m_pCameraModule->m_bHDR = false;
	RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender()->Render(m_pCameraModule,EditorApplication::GetInstance()->m_pGizmoScene,m_pRenderView);
	m_pCameraModule->m_bHDR = bCameraHDR;
}


