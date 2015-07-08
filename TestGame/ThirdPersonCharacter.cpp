#include "stdafx.h"
#include "ThirdPersonCharacter.h"
#include "IWorldObj.h"
#include "InputInterface.h"
#include "InputManager.h"
#include "TimeManager.h"
ThirdPersonCharacter::ThirdPersonCharacter()
	:m_fYaw(0.0f)
	, m_fDistToCamera(400)
{
}


ThirdPersonCharacter::~ThirdPersonCharacter()
{
}

void ThirdPersonCharacter::OnInput()
{
	float fSpeed = 0.0f;
	float fRotSpeed = 1.3f;
	SmartPointer<InputInterface> pInterface = InputManager::GetInstance()->m_pIO;
	Vector3 vecPos = m_pObj->m_pTransform->GetWorldTranslate();
	if (pInterface->IsKeyDown('W') == true)
	{
		fSpeed = 1500.0f;

		PlayAnimation("walk");
	}
	else if (pInterface->IsKeyDown('S') == true)
	{
		PlayAnimation("walk");
		fSpeed = -1500.0f;
	}
	else
	{
		PlayAnimation("idle");
	}
	if (pInterface->IsKeyDown('A') == true)
	{
		m_fYaw -= fRotSpeed * TimeManager::GetInstance()->m_fElapseTime;
	}
	if (pInterface->IsKeyDown('D') == true)
	{
		m_fYaw += fRotSpeed * TimeManager::GetInstance()->m_fElapseTime;
	}
	m_fDistToCamera -= pInterface->GetMouseWheel() * 0.05f;
	if (m_fDistToCamera < 100)
	{
		m_fDistToCamera = 100;
	}
	if (m_fDistToCamera > 1000)
	{
		m_fDistToCamera = 1000;
	}
	//
	Vector3 rot = m_pObj->m_pTransform->GetRotation();
	rot.m_fy = m_fYaw;
	m_pObj->m_pTransform->SetOrientation(rot.m_fx, rot.m_fy, rot.m_fz);

	Vector3 cameraRot = m_pCamera->m_pTransform->GetRotation();
	cameraRot.m_fy = m_fYaw;
	m_pCamera->m_pTransform->SetOrientation(cameraRot.m_fx, cameraRot.m_fy, cameraRot.m_fz);
	//
	Vector3 forwardDir = m_pObj->m_pTransform->GetForward();
	vecPos = forwardDir * fSpeed * TimeManager::GetInstance()->m_fElapseTime + vecPos;
	m_pObj->m_pTransform->SetWorldTranslate(vecPos);
	m_pObj->m_pTransform->Update();



	m_pCamera->Update();
	Vector3 cameraDir = m_pCamera->m_pTransform->GetForward();
	Vector3 vecCameraPos = m_pObj->m_pTransform->GetWorldTranslate() - cameraDir * m_fDistToCamera + Vector3(0.0f, 30.0f, 0.0f);
	m_pCamera->m_pTransform->SetWorldTranslate(vecCameraPos);
}
