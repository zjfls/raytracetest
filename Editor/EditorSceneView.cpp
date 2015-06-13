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
#include "Ray3D.h"
#include "BoundingBase.h"
#include "IRenderable.h"
#include "IntersectTest.h"
#include "GizmoManager.h"
#include "TranslateGizmo.h"
#include "Vector4.h"
#include "FbxAsset.h"
#include <algorithm>
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
	if (m_bShow == false)
	{
		return;
	}



	//std::cout << "scene end" << std::endl;
	if (m_bIsFocus)
	{
		//std::cout << "UpdateCamera" << std::endl;
		UpdateCamera();
	}





	m_pCamera->Update();
	m_pCamera->AfterUpdate();
	//
	UpdateGizmo();
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
		vecRot.m_fy = vecRot.m_fy + (diff.m_fx) * 0.0014;
		vecRot.m_fx = vecRot.m_fx + (diff.m_fy) * 0.0014;
		m_pCamera->m_pTransform->SetOrientation(vecRot.m_fx, vecRot.m_fy, vecRot.m_fz);


		
	}
	if (EditorApplication::GetInstance()->m_eOperState == EditorApplication::EStateTranslate
		&&EditorApplication::GetInstance()->m_SelectObj != nullptr)
	{
		if (EditorApplication::GetInstance()->m_eSelState == EditorApplication::ESelNone)
		{

		}
		else
		{
			//
			Vector3 vecDiff = m_pCamera->m_pTransform->GetWorldTranslate() - EditorApplication::GetInstance()->m_SelectObj->m_pTransform->GetWorldTranslate();
			float zValue = vecDiff.length();
			float yValue = zValue * tan(m_pCameraModule->m_fFovy / 2);
			float xValue = yValue * m_pCameraModule->m_fAspect;

			Vector3 movDir = Vector3::ZERO;
			//
			int nWidth = m_pRenderView->m_nWidth;
			int nHeight = m_pRenderView->m_nHeight;
			//
			Vector2 diff = pt - m_LastMousePos;
			//std::cout << "diffy:" << diff.m_fy << std::endl;
			//
			float fMoveDist = 0.0f;
			switch (EditorApplication::GetInstance()->m_eSelState)
			{
				case EditorApplication::ETranslateUp:
				{
					movDir = Vector3::YAxis;
					Vector4 screenDir;
					screenDir.Vector3ToDirection(movDir);
					screenDir = screenDir * m_pCameraModule->m_MatViewProj;
					Vector2 vec2Screen;
					vec2Screen.m_fx = screenDir.m_fx;
					vec2Screen.m_fy = screenDir.m_fy;
					vec2Screen.normalize();

					fMoveDist = -diff.m_fy * vec2Screen.m_fy * yValue / nHeight + diff.m_fx * vec2Screen.m_fx * xValue / nWidth;


					
					//fMoveDist = -diff.m_fy * yValue / nHeight;
				}
				break;
				case EditorApplication::ETranslateForward:
				{
					movDir = Vector3::ZAxis;
					Vector4 screenDir;
					screenDir.Vector3ToDirection(movDir);
					screenDir = screenDir * m_pCameraModule->m_MatViewProj;
					Vector2 vec2Screen;
					vec2Screen.m_fx = screenDir.m_fx;
					vec2Screen.m_fy = screenDir.m_fy;
					vec2Screen.normalize();

					fMoveDist = -diff.m_fy * vec2Screen.m_fy * yValue / nHeight + diff.m_fx * vec2Screen.m_fx * xValue / nWidth;

				}
				break;
				case EditorApplication::ETranslateRight:
				{
					movDir = Vector3::XAxis;
					Vector4 screenDir;
					screenDir.Vector3ToDirection(movDir);
					screenDir = screenDir * m_pCameraModule->m_MatViewProj;
					//
					Vector2 vec2Screen;
					vec2Screen.m_fx = screenDir.m_fx;
					vec2Screen.m_fy = screenDir.m_fy;
					vec2Screen.normalize();

					fMoveDist = -diff.m_fy * vec2Screen.m_fy * yValue / nHeight + diff.m_fx * vec2Screen.m_fx * xValue / nWidth;
				}
				break;
				default:
				break;
			}
			Vector3 worldPos = EditorApplication::GetInstance()->m_SelectObj->m_pTransform->GetWorldTranslate();
			worldPos = fMoveDist * movDir + worldPos;
			EditorApplication::GetInstance()->m_SelectObj->m_pTransform->SetWorldTranslate(worldPos);


		}
	}
	m_LastMousePos = pt;
}

void EditorSceneView::OnMouseLButtonDown(Vector2& pos)
{
	EditorApplication::EOperationState eOperState = EditorApplication::GetInstance()->m_eOperState;
	if (EditorApplication::GetInstance()->m_SelectObj != nullptr)
	{
		switch (eOperState)
		{
			case EditorApplication::EStateTranslate:
			{
				SmartPointer<CameraBase> pCameraModule = m_pCamera->GetModule(1).SmartPointerCast<CameraBase>();
				Vector3 worldDir = PickUtil::ScreenPosToWorldDir(pos, pCameraModule, m_pRenderView->m_nWidth, m_pRenderView->m_nHeight);
				Ray3D r(pCameraModule->m_pOwnerObj->m_pTransform->GetWorldTranslate(), worldDir);

				std::vector<SmartPointer<IRenderable>> vecRends;
				GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->GetAllModuleRecursive<IRenderable>(vecRends);
				for each (SmartPointer<IRenderable> pRend in vecRends)
				{
					BoundingBase* pBound = pRend->m_pBounding;
					if (IntersectTest::Ray_BoundingTest(r, *pBound, pCameraModule->m_fNear, pCameraModule->m_fFar) == true)
					{
						IntersectResults result = IntersectTest::testRayRenderable(r, *pRend.get(), *pRend->m_pOwnerObj->m_pTransform);
						if (result.m_bInterset == true)
						{
							result.sortNearFirst();
							IRenderable* pRend = result.m_vecIntersetDatas[0].pRender;
							const char* pName = pRend->m_strName.c_str();
							if (strstr(pRend->m_strName.c_str(), "UP") != nullptr)
							{
								EditorApplication::GetInstance()->m_eSelState = EditorApplication::ETranslateUp;
								m_LastMousePos = pos;
								//std::cout << "up" << std::endl;
							}
							else if (strstr(pRend->m_strName.c_str(), "RIGHT") != nullptr)
							{
								EditorApplication::GetInstance()->m_eSelState = EditorApplication::ETranslateRight;
								m_LastMousePos = pos;
								//std::cout << "right" << std::endl;
							}
							else if (strstr(pRend->m_strName.c_str(), "FORWARD") != nullptr)
							{
								EditorApplication::GetInstance()->m_eSelState = EditorApplication::ETranslateForward;
								m_LastMousePos = pos;
								//std::cout << "forward" << std::endl;
							}
						}
					}
				}
				//for each (SmartPointer<IRenderable> pRend in vecRightRends)
				//{

				//}
				//for each (SmartPointer<IRenderable> pRend in vecForwardRends)
				//{

				//}
			}
			break;
		}
	}
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
	SmartPointer<CameraBase> pCameraModule = m_pCamera->GetModule(1).SmartPointerCast<CameraBase>();
	Vector3 worldPos = PickUtil::ScreenPosToWorldPos(pos, 500, pCameraModule, m_pRenderView->m_nWidth, m_pRenderView->m_nHeight);
	const char* strPath = path.c_str() + 8;

	std::transform(filesuffix.begin(), filesuffix.end(), filesuffix.begin(), tolower);
	if (filesuffix == "prefab.xml")
	{
		AssetManager::GetInstance()->LoadAsset(strPath);
		SmartPointer<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->GetResource(strPath);
		SmartPointer<IWorldObj> pObj = pPrefab->m_pRoot->Clone(true);



		//m_pTargetObj = pObj;
		EditorApplication::GetInstance()->m_pWorld->m_pRoot->addChild(pObj);
		pObj->m_pTransform->SetTranslate(worldPos);

		EditorApplication::GetInstance()->NotifyListener("InitScene", EditorApplication::GetInstance());
	}
	if (filesuffix == "fbx")
	{
		FbxAsset* pAsset = (FbxAsset*)AssetManager::GetInstance()->LoadAsset(strPath);
		SmartPointer<PrefabResource> pPrefab = pAsset->getPrefabResource();
		if (pPrefab != nullptr)
		{
			SmartPointer<IWorldObj> pObj = pPrefab->m_pRoot->Clone(true);



			//m_pTargetObj = pObj;
			EditorApplication::GetInstance()->m_pWorld->m_pRoot->addChild(pObj);
			pObj->m_pTransform->SetTranslate(worldPos);

			EditorApplication::GetInstance()->NotifyListener("InitScene", EditorApplication::GetInstance());
		}

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
		//std::cout << "move front:" << "x:" << diff.m_fx << "y:" << diff.m_fy << "z:" << diff.m_fz << "ElapseTime:" << TimeManager::GetInstance()->m_fElapseTime << std::endl;
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
		//std::cout << "move front:" << "x:" << diff.m_fx << "y:" << diff.m_fy << "z:" << diff.m_fz << "ElapseTime:" << TimeManager::GetInstance()->m_fElapseTime << std::endl;
		position += diff;
		m_pCamera->m_pTransform->SetTranslate(position);
	}
}

//void EditorSceneView::OnClick(Vector2& pos)
//{
//
//}

void ZG::EditorSceneView::OnClick(Vector2& pos)
{
	switch (EditorApplication::GetInstance()->m_eOperState)
	{
		case EditorApplication::EStateTranslate:
		{
			if (EditorApplication::GetInstance()->m_eSelState != EditorApplication::ESelNone)
			{
				break;
			}
			SmartPointer<CameraBase> pCameraModule = m_pCamera->GetModule(1).SmartPointerCast<CameraBase>();
			Vector3 worldDir = PickUtil::ScreenPosToWorldDir(pos, pCameraModule, m_pRenderView->m_nWidth, m_pRenderView->m_nHeight);
			Ray3D r(pCameraModule->m_pOwnerObj->m_pTransform->GetWorldTranslate(), worldDir);

			std::vector<SmartPointer<IRenderable>> vecRend;
			EditorApplication::GetInstance()->m_pWorld->m_pRoot->GetAllModuleRecursive<IRenderable>(vecRend);
			for each (SmartPointer<IRenderable> pRend in vecRend)
			{
				BoundingBase* pBound = pRend->m_pBounding;
				if (IntersectTest::Ray_BoundingTest(r, *pBound, pCameraModule->m_fNear, pCameraModule->m_fFar) == true)
				{
					//std::cout << "click obj:" << pRend->m_pOwnerObj->m_strName << std::endl;
					IntersectResults result = IntersectTest::testRayRenderable(r, *pRend.get(), *pRend->m_pOwnerObj->m_pTransform);
					if (result.m_bInterset == true)
					{
						EditorApplication::GetInstance()->m_SelectObj = pRend->m_pOwnerObj;
						EditorApplication::GetInstance()->NotifyListener("SelectChange", EditorApplication::GetInstance());
					}
				}
			}
		}
		break;
		default:
		break;
	}

}

void ZG::EditorSceneView::UpdateGizmo()
{


	EditorApplication::EOperationState eOperState = EditorApplication::GetInstance()->m_eOperState;
	if (EditorApplication::GetInstance()->m_SelectObj != nullptr)
	{
		switch (eOperState)
		{
			case EditorApplication::EStateTranslate:
			{
				Vector3 dir = EditorApplication::GetInstance()->m_SelectObj->m_pTransform->GetWorldTranslate() - m_pCamera->m_pTransform->GetWorldTranslate();
				dir.normalize();
				GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetTranslate(m_pCamera->m_pTransform->GetWorldTranslate() + dir * 200);
				//GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetTranslate(m_SelectObj->m_pTransform->GetWorldTranslate());
			}
			break;
		}
	}
}

void ZG::EditorSceneView::OnMouseLButtonRelease(Vector2& pt)
{
	EditorApplication::GetInstance()->m_eSelState = EditorApplication::ESelNone;
}

void EditorSceneView::DrawGizmo()
{
	bool bCameraHDR = m_pCameraModule->m_bHDR;
	m_pCameraModule->m_bHDR = false;
	m_pCameraModule->m_bClearColor = false;
	m_pCameraModule->m_bClearDepth = false;
	//std::cout << "draw gizmo render" << std::endl;
	RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender()->Render(m_pCameraModule, EditorApplication::GetInstance()->m_pGizmoScene, m_pRenderView);
	m_pCameraModule->m_bHDR = bCameraHDR;
	m_pCameraModule->m_bClearColor = true;
	m_pCameraModule->m_bClearDepth = true;
	//std::cout << "draw gizmo end" << std::endl;
}


