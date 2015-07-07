#include "stdafx.h"
#include "ThirdPersonCharacter.h"
#include "IWorldObj.h"
#include "InputInterface.h"
#include "InputManager.h"
#include "TimeManager.h"
ThirdPersonCharacter::ThirdPersonCharacter()
{
}


ThirdPersonCharacter::~ThirdPersonCharacter()
{
}

void ThirdPersonCharacter::OnInput()
{
	float fSpeed = 0.0f;
	SmartPointer<InputInterface> pInterface = InputManager::GetInstance()->m_pIO;
	Vector3 vecPos = m_pObj->m_pTransform->GetWorldTranslate();
	if (pInterface->IsKeyDown('W') == true)
	{
		fSpeed = 500.0f;

		PlayAnimation("walk");
	}
	else if (pInterface->IsKeyDown('S') == true)
	{
		PlayAnimation("walk");
		fSpeed = -500.0f;
	}
	else
	{
		PlayAnimation("idle");
	}
	Vector3 forwardDir = m_pObj->m_pTransform->GetForward();
	vecPos = forwardDir * fSpeed * TimeManager::GetInstance()->m_fElapseTime + vecPos;
	m_pObj->m_pTransform->SetWorldTranslate(vecPos);

	Vector3 cameraDir = m_pCamera->m_pTransform->GetForward();


	Vector3 vecCameraPos = vecPos - cameraDir * 1000 + Vector3(0.0f,200.0f,0.0f);
	m_pCamera->m_pTransform->SetWorldTranslate(vecCameraPos);
}
