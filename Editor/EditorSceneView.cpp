#include "stdafx.h"
#include "EditorSceneView.h"
#include "IWorldObj.h"
#include "RasterCamera.h"
#include "MathDefine.h"
#include "CameraRenderer.h"
#include "EditorApplication.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "MathFunc.h"
#include "IOManager.h"
#include "TimeManager.h"

EditorSceneView::EditorSceneView()
{
	//
	m_pCamera = std::shared_ptr<IWorldObj>(IWorldObj::CreateWorldObj());
	m_pCamera->m_strName = "EditorSceneCamera";

	shared_ptr<RasterCamera> pCameraModule = m_pCamera->addModule<RasterCamera>(m_pCamera);
	pCameraModule->m_fFar = 2000.0f;
	pCameraModule->m_fNear = 3.0f;
	pCameraModule->m_fAspect = 1 / 1;
	pCameraModule->m_fFovy = PI / 4;
	//
	std::shared_ptr<CameraRenderer> pCameraRenderer(new CameraRenderer);// = new CameraRenderer;
	pCameraRenderer->m_pWorld = EditorApplication::GetInstance()->m_pWorld;
	//pCameraRenderer->m_pTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderView();
	pCameraRenderer->m_pRender = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRender();
	pCameraRenderer->m_clrColr = GameColor::blue;
	pCameraModule->AddListener("CameraRenderer", pCameraRenderer);
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





	//
	m_pCamera->Update();
	m_pCamera->AfterUpdate();
	m_pRenderView->Present();
}

void EditorSceneView::Resize(unsigned int nWidth, unsigned int nHeight)
{
	std::shared_ptr<RasterCamera> pCameraModule = dynamic_pointer_cast<RasterCamera>(m_pCamera->GetModule(1));
	std::shared_ptr<CameraRenderer> pCameraRenderer = dynamic_pointer_cast<CameraRenderer>(pCameraModule->m_mapListener["CameraRenderer"]);
	pCameraModule->m_fAspect = float(nWidth) / nHeight;
	EditorRenderView::Resize(nWidth, nHeight);
}

void EditorSceneView::OnMouseWheel(short zDelta, Vector2& pt)
{
	Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
	Vector3 dir = m_pCamera->m_pTransform->GetForward();
	dir = dir.normalize();
	//
	position += zDelta * 0.1 * dir;
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
		vecRot.m_fy = vecRot.m_fy + (diff.m_fx) * 0.0001;
		vecRot.m_fx = vecRot.m_fx + (diff.m_fy) * 0.0001;
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
	if (key == 'W')
	{
		
		Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
		Vector3 dir = m_pCamera->m_pTransform->GetForward();
		dir = dir.normalize();
		//
		Vector3 diff = 1000 * TimeManager::GetInstance()->m_fElapseTime * dir;
		std::cout << "move front:"<<"x:"<<diff.m_fx<<"y:"<<diff.m_fy<<"z:"<<diff.m_fz<<"ElapseTime:"<<TimeManager::GetInstance()->m_fElapseTime << std::endl;
		position += diff;
		m_pCamera->m_pTransform->SetTranslate(position);
	}
	if (key == 'S')
	{
		Vector3 position = m_pCamera->m_pTransform->GetLocalTranslate();
		Vector3 dir = m_pCamera->m_pTransform->GetForward();
		dir = dir.normalize();
		//
		Vector3 diff = 1000 * TimeManager::GetInstance()->m_fElapseTime * dir;
		position = position - diff;
		m_pCamera->m_pTransform->SetTranslate(position);
	}
}
