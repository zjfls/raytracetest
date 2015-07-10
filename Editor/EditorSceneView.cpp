#include "stdafx.h"
#include "EditorSceneView.h"
#include "IWorldObj.h"
#include "RasterCamera.h"
#include "MathDefine.h"
#include "EditorApplication.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "MathFunc.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "PickUtil.h"
#include "PrefabResource.h"
#include "AssetManager.h"
#include "FilePath.h"
#include "RasterCamera.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "InputInterface.h"
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
#include "EditorCommands.h"
#include "EditorCommandManager.h"
#include "AABBBox.h"
#include "Matrix44.h"
#include "Ray3D.h"
#include "Plane3D.h"
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
	pCameraModule->m_pWorld = EditorApplication::GetInstance()->m_pWorld.get();
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
	float fRatio = 1.0f - zDelta * 0.0001;
	if (fRatio < 0.8)
	{
		fRatio = 0.8f;
	}
	if (fRatio > 1.2)
	{
		fRatio = 1.2f;
	}

	//float fDist = 100.0f;
	if (EditorApplication::GetInstance()->getSelectObj() != nullptr)
	{
		Vector3 vSelect = EditorApplication::GetInstance()->getSelectObj()->m_pTransform->GetWorldTranslate();
		Vector3 diff = position - vSelect;
		float length = diff.length();

		position = vSelect + diff * fRatio;
	}
	else
	{
		position = position + dir * zDelta * 0.2;
	}
	m_pCamera->m_pTransform->SetTranslate(position);
	//
}

void EditorSceneView::OnMouseMove(Vector2& pt)
{
	if (InputManager::GetInstance()->m_pIO->IsMiddleDown() == true)
	{
		Vector2 diffMouse = pt - m_LastMousePos;
		Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
		Vector3 dirRight = m_pCamera->m_pTransform->GetRight();
		dirRight = dirRight.normalize();

		Vector3 dirUp = m_pCamera->m_pTransform->GetUp();
		dirUp = dirUp.normalize();
		//
		Vector3 diff = -diffMouse.m_fx  * dirRight;
		diff = diff + diffMouse.m_fy * dirUp;
		//std::cout << "move front:" << "x:" << diff.m_fx << "y:" << diff.m_fy << "z:" << diff.m_fz << "ElapseTime:" << TimeManager::GetInstance()->m_fElapseTime << std::endl;
		position += diff;
		m_pCamera->m_pTransform->SetTranslate(position);
	}
	if (InputManager::GetInstance()->m_pIO->IsRBDown() == true)
	{
		if (InputManager::GetInstance()->m_pIO->IsKeyDown(0x12) == true && EditorApplication::GetInstance()->getSelectObj() != nullptr)
		{
			//std::cout << "rot about target" << std::endl;
			Vector2 diff = pt - m_LastMousePos;
			Vector3 vecRot = m_pCamera->m_pTransform->GetRotation();
			//Vector3 vecRot = rot.m_vecEulerAngle;
			vecRot.m_fy = vecRot.m_fy + (diff.m_fx) * 0.0034;
			vecRot.m_fx = vecRot.m_fx + (diff.m_fy) * 0.0034;
			//
			Vector3 vecWorld = EditorApplication::GetInstance()->getSelectObj()->m_pTransform->GetWorldTranslate();
			Vector3 vecCamera = m_pCameraModule->GetViewMatrix().TransformPosition(vecWorld);
			//
			m_pCamera->m_pTransform->SetOrientation(vecRot.m_fx, vecRot.m_fy, vecRot.m_fz);
			//
			m_pCamera->m_pTransform->Update();
			m_pCameraModule->Update();


			Matrix44 matView = m_pCameraModule->m_MatInverseView;
			matView.M[3][0] = 0.0f;
			matView.M[3][1] = 0.0f;
			matView.M[3][2] = 0.0f;
			Vector3 vecNewWorld = matView.TransformPosition(vecCamera);
			Vector3 vecPos = vecWorld - vecNewWorld;
			m_pCamera->m_pTransform->SetWorldTranslate(vecPos);

			//Vector3 vecTarget = EditorApplication::GetInstance()->getSelectObj()->m_pTransform->GetWorldTranslate();
			//Vector3 vecDir = Vector3(0.0f, 1.0f, 0.0f);
			//vecTarget = vecTarget - 10000 * vecDir;
			//Ray3D r(vecTarget, vecDir);
			////
			//Plane3D p(m_pCamera->m_pTransform->GetWorldTranslate(), m_pCamera->m_pTransform->GetUp());
			////
			//IntersectResults result = IntersectTest::testRayPlane(r, p, *m_pCamera->m_pTransform);
			//float dist = 0.0f;
			//if (result.m_bInterset == true)
			//{
			//	vecTarget = result.m_vecIntersetDatas[0].vecPos;
			//}
			//

			//float dist = (vecTarget - m_pCamera->m_pTransform->GetWorldTranslate()).length();
			//Vector3 dir = m_pCamera->m_pTransform->GetForward();


			//Vector3 newPos = vecTarget - dir * dist;
			//m_pCamera->m_pTransform->SetWorldTranslate(newPos);

		}
		else
		{
			Vector2 diff = pt - m_LastMousePos;
			//std::cout << "mouse move with rb down "<<"x:"<<pt.m_fx<<"y:"<<pt.m_fy << std::endl;
			Vector3 vecRot = m_pCamera->m_pTransform->GetRotation();
			//Vector3 vecRot = rot.m_vecEulerAngle;
			vecRot.m_fy = vecRot.m_fy + (diff.m_fx) * 0.0014;
			vecRot.m_fx = vecRot.m_fx + (diff.m_fy) * 0.0014;
			m_pCamera->m_pTransform->SetOrientation(vecRot.m_fx, vecRot.m_fy, vecRot.m_fz);
		}		
	}
	if (EditorApplication::GetInstance()->m_eOperState == EditorApplication::EStateTranslate
		&&EditorApplication::GetInstance()->getSelectObj() != nullptr)
	{
		if (EditorApplication::GetInstance()->m_eSelState == EditorApplication::ESelNone)
		{

		}
		else
		{
			//
			Vector3 vecDiff = m_pCamera->m_pTransform->GetWorldTranslate() - EditorApplication::GetInstance()->getSelectObj()->m_pTransform->GetWorldTranslate();
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

			for (int i = 0; i < EditorApplication::GetInstance()->GetSelectionCount(); ++i)
			{
				IWorldObj* pSelObj = EditorApplication::GetInstance()->GetSelectionByIndex(i);
				Vector3 worldPos = pSelObj->m_pTransform->GetWorldTranslate();
				worldPos = fMoveDist * movDir + worldPos;
				//std::cout << "move dist" << fMoveDist << std::endl;
				pSelObj->m_pTransform->SetWorldTranslate(worldPos);
			}

		}
	}
	m_LastMousePos = pt;
}

void EditorSceneView::OnMouseLButtonDown(Vector2& pos)
{
	EditorApplication::EOperationState eOperState = EditorApplication::GetInstance()->m_eOperState;
	if (EditorApplication::GetInstance()->getSelectObj() != nullptr)
	{
		switch (eOperState)
		{
			case EditorApplication::EStateTranslate:
			{
				
				SmartPointer<CameraBase> pCameraModule = m_pCamera->GetModule(1).SmartPointerCast<CameraBase>();
				//std::cout << "clicked:" << m_pRenderView->m_nWidth<<" " << m_pRenderView->m_nHeight << std::endl;
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
								EditorApplication::GetInstance()->StartTranslate();
								//std::cout << "up" << std::endl;
							}
							else if (strstr(pRend->m_strName.c_str(), "RIGHT") != nullptr)
							{
								EditorApplication::GetInstance()->m_eSelState = EditorApplication::ETranslateRight;
								m_LastMousePos = pos;
								EditorApplication::GetInstance()->StartTranslate();
								//std::cout << "right" << std::endl;
							}
							else if (strstr(pRend->m_strName.c_str(), "FORWARD") != nullptr)
							{
								EditorApplication::GetInstance()->m_eSelState = EditorApplication::ETranslateForward;
								m_LastMousePos = pos;
								EditorApplication::GetInstance()->StartTranslate();
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
		



		AddToSceneCommand* pCmd = new AddToSceneCommand();
		pCmd->m_pObj = pObj;
		pCmd->m_pParentObj = EditorApplication::GetInstance()->m_pWorld->m_pRoot;
		pCmd->m_pReceiver = EditorApplication::GetInstance();
		EditorCommandManager::GetInstance()->ExcuteNewCmd(pCmd);
		pObj->Update();
		pObj->m_pTransform->SetWorldTranslate(worldPos);

	}
	if (filesuffix == "fbx")
	{
		FbxAsset* pAsset = (FbxAsset*)AssetManager::GetInstance()->LoadAsset(strPath);
		SmartPointer<PrefabResource> pPrefab = pAsset->getPrefabResource();
		if (pPrefab != nullptr)
		{
			SmartPointer<IWorldObj> pObj = pPrefab->m_pRoot->Clone(true);
			


			AddToSceneCommand* pCmd = new AddToSceneCommand();
			pCmd->m_pObj = pObj;
			pCmd->m_pParentObj = EditorApplication::GetInstance()->m_pWorld->m_pRoot;
			pCmd->m_pReceiver = EditorApplication::GetInstance();
			EditorCommandManager::GetInstance()->ExcuteNewCmd(pCmd);
			pObj->Update();
			pObj->m_pTransform->SetWorldTranslate(worldPos);
			//m_pTargetObj = pObj;

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
	SmartPointer<InputInterface> pInterface = InputManager::GetInstance()->m_pIO;
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

			float fNearst = MAXFLOAT;
			IWorldObj* pClickedObj = nullptr;
			for each (SmartPointer<IRenderable> pRend in vecRend)
			{
				BoundingBase* pBound = pRend->m_pBounding;
				if (IntersectTest::Ray_BoundingTest(r, *pBound, pCameraModule->m_fNear, pCameraModule->m_fFar) == true)
				{
					//std::cout << "click obj:" << pRend->m_pOwnerObj->m_strName << std::endl;
					IntersectResults result = IntersectTest::testRayRenderable(r, *pRend.get(), *pRend->m_pOwnerObj->m_pTransform);
					result.sortNearFirst();
					if (result.m_bInterset == true)
					{
						if (result.m_vecIntersetDatas[0].fDist < fNearst)
						{
							pClickedObj = pRend->m_pOwnerObj;
							fNearst = result.m_vecIntersetDatas[0].fDist;
						}
					}
				}
			}
			if (pClickedObj != nullptr)
			{
				if (InputManager::GetInstance()->m_pIO->IsKeyDown(InputInterface::KeyCode::EKEYCTRL))
				{
					EditorApplication::GetInstance()->AddSelection(pClickedObj);
				}
				else
				{
					EditorApplication::GetInstance()->SelectChange(pClickedObj);
					//EditorApplication::GetInstance()->NotifyListener("SelectChange", EditorApplication::GetInstance());
				}

			}
			else
			{
				EditorApplication::GetInstance()->SelectChange(nullptr);
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
	if (EditorApplication::GetInstance()->getSelectObj() != nullptr)
	{
		switch (eOperState)
		{
			case EditorApplication::EStateTranslate:
			{
				Vector3 dir = EditorApplication::GetInstance()->GetSelectionsWorldTranslate() - m_pCamera->m_pTransform->GetWorldTranslate();
				dir.normalize();
				GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetTranslate(m_pCamera->m_pTransform->GetWorldTranslate() + dir * 250);
				//GizmoManager::GetInstance()->m_pTranslateGizmo->m_pRoot->m_pTransform->SetTranslate(m_SelectObj->m_pTransform->GetWorldTranslate());
			}
			break;
		}
	}
}

void ZG::EditorSceneView::OnMouseLButtonRelease(Vector2& pt)
{
	if (EditorApplication::GetInstance()->m_eSelState != EditorApplication::ESelNone)
	{
		EditorApplication::GetInstance()->EndTranslate();
	}
	
}

void ZG::EditorSceneView::FocusTarget(IWorldObj* pObj)
{
	AABBBox aabb = pObj->GetWorldAABBBox();
	aabb.Transform(m_pCameraModule->GetViewMatrix());
	Vector3 diff = aabb.m_Max - aabb.m_Min;
	Vector3 center = (aabb.m_Max + aabb.m_Min) * 0.5f;
	center = Matrix44::QuikInverse(m_pCameraModule->GetViewMatrix()).TransformPosition(center);
	float fovy = m_pCameraModule->m_fFovy;
	float yTan = tan(fovy / 2.0f);
	float disty = diff.m_fy / yTan;
	float xTan = yTan * m_pCameraModule->m_fAspect;
	float distx = diff.m_fx / xTan;
	if (distx < disty)
	{
		distx = disty;
	}
	//
	distx = distx;

	Vector3 worldPos = pObj->m_pTransform->GetWorldTranslate();
	Vector3 dir = -m_pCameraModule->m_pOwnerObj->m_pTransform->GetForward();
	worldPos = center + dir * distx;
	m_pCameraModule->m_pOwnerObj->m_pTransform->SetWorldTranslate(worldPos);
}

void ZG::EditorSceneView::OnMouseMButtonDown(Vector2& pt)
{
	m_LastMousePos = pt;
}

void ZG::EditorSceneView::OnMouseMButtonRelease(Vector2& pt)
{

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


