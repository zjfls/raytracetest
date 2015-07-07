#include "stdafx.h"
#include "GameRuntime.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "CameraBase.h"
#include "Transform.h"
#include "IWorldObj.h"
#include "FilePath.h"
#include "IAsset.h"
#include "AssetManager.h"
#include <algorithm>
#include "PrefabResource.h"
#include "CharacterController.h"
#include "GameApp.h"
#include "ThirdPersonCharacter.h"
#include "IAsset.h"
#include "AssetManager.h"
#include "AnimationResource.h"
#include "AnimationTrack.h"
#include "skeleton.h"
#include "SkeletonResource.h"
//
GameRuntime::GameRuntime()
{
}


GameRuntime::~GameRuntime()
{
}

SmartPointer<ModuleBase> GameRuntime::Clone()
{
	return nullptr;
}

void GameRuntime::OnUpdate()
{
	
}

void GameRuntime::OnLateUpdate()
{
	UpdateInput();
}

void GameRuntime::UpdateInput()
{
	//GetFocus();
	UpdateCamera();
	UpdateCharacter();
}

void GameRuntime::UpdateCamera()
{
	return;
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
	Vector3 rot = m_pCamera->m_pTransform->GetRotation();
	if (pInterface->IsKeyDown('E') == true)
	{
		rot.m_fx += TimeManager::GetInstance()->m_fElapseTime * 1.0f;
	}
	if (pInterface->IsKeyDown('R') == true)
	{
		rot.m_fx -= TimeManager::GetInstance()->m_fElapseTime * 1.0f;
	}
	if (pInterface->IsKeyDown('F') == true)
	{
		rot.m_fy += TimeManager::GetInstance()->m_fElapseTime * 1.0f;
	}
	if (pInterface->IsKeyDown('G') == true)
	{
		rot.m_fy -= TimeManager::GetInstance()->m_fElapseTime * 1.0f;
	}
	m_pCamera->m_pTransform->SetOrientation(rot.m_fx, rot.m_fy, rot.m_fz);
}

CharacterController* GameRuntime::createCharacterController(std::string fileName)
{
	std::string strSuffix = getFileSuffix(fileName);
	IAsset* pAsset;
	std::transform(strSuffix.begin(), strSuffix.end(), strSuffix.begin(), tolower);
	pAsset = AssetManager::GetInstance()->LoadAsset(fileName);
	//if (strstr(strSuffix.c_str(), "fbx") != nullptr)
	//{
	//	
	//}
	//else if (strstr(strSuffix.c_str(), "prefab.xml") != nullptr)
	//{

	//}
	PrefabResource* pRes = pAsset->GetResource<PrefabResource>();
	if (pRes != nullptr)
	{
		SmartPointer<IWorldObj> pObj = pRes->m_pRoot->Clone(true).get();
		CharacterController* pCtrller = new CharacterController();

		pCtrller->m_pObj = pObj.get();


		GameApp::GetInstance()->m_pWorld->m_pRoot->addChild(pObj);

		m_vecCharacter.push_back(pCtrller);


		return pCtrller;
	}

	

	return nullptr;
}

void GameRuntime::UpdateCharacter()
{
	if (m_pThirdPersion != nullptr)
	{
		m_pThirdPersion->OnInput();
	}
}

ThirdPersonCharacter* GameRuntime::createThirdPerson(std::string fileName)
{
	std::string strSuffix = getFileSuffix(fileName);
	IAsset* pAsset;
	std::transform(strSuffix.begin(), strSuffix.end(), strSuffix.begin(), tolower);
	pAsset = AssetManager::GetInstance()->LoadAsset(fileName);
	//if (strstr(strSuffix.c_str(), "fbx") != nullptr)
	//{
	//	
	//}
	//else if (strstr(strSuffix.c_str(), "prefab.xml") != nullptr)
	//{

	//}
	PrefabResource* pRes = pAsset->GetResource<PrefabResource>();
	if (pRes != nullptr)
	{
		SmartPointer<IWorldObj> pObj = pRes->m_pRoot->Clone(true).get();
		ThirdPersonCharacter* pCtrller = new ThirdPersonCharacter();

		pCtrller->m_pObj = pObj.get();
		//IAsset* pAniAsset = AssetManager::GetInstance()->LoadAsset("./data/fbx/kulouanim/attack.animation.xml");
		//AnimationResource* pAniRes = pAniAsset->GetResource<AnimationResource>();
		////
		//AnimationTrack* pTrack = new AnimationTrack(pAniRes);
		//SkeletonModule* pSkeleton = pCtrller->m_pObj->GetModule<SkeletonModule>();// ->AddAnimationTrack(pTrack);
		////
		//pCtrller->m_pAnimations["walk"] = pSkeleton->m_pDefaultTrack;
		//pCtrller->m_pAnimations["attack"] = pTrack;
		////
		//pSkeleton->AddAnimationTrack(pTrack);
		//pSkeleton->m_pDefaultTrack = pTrack;
		m_pThirdPersion = pCtrller;
		pCtrller->LoadAnimation("idle", "./data/fbx/kulouanim/idle.animation.xml");
		pCtrller->LoadAnimation("walk", "./data/fbx/kulouanim/walk.animation.xml");
		pCtrller->LoadAnimation("dance", "./data/fbx/kulouanim/dance.animation.xml");
		pCtrller->LoadAnimation("attack", "./data/fbx/kulouanim/attack.animation.xml");

		pCtrller->PlayAnimation("dance");

		GameApp::GetInstance()->m_pWorld->m_pRoot->addChild(pObj);
		pCtrller->m_pCamera = m_pCamera;

		//
		m_vecCharacter.push_back(pCtrller);


		return pCtrller;
	}
}
