#include "stdafx.h"
#include "GameApp.h"
#include "IAsset.h"
#include "AssetManager.h"
#include "IWorldObj.h"
#include "AnimationResource.h"
#include "SceneResource.h"
#include "IWorld.h"
#include "CameraBase.h"
#include "IWorldObj.h"
#include "RasterCamera.h"
#include "RenderManager.h"
#include "IRender.h"
#include "MathDefine.h"
#include "RenderSystem.h"
#include "RasterRender.h"
#include "MathFunc.h"
#include "GameRuntime.h"
#include "CharacterController.h"
#include "Skeleton.h"
#include "AnimationTrack.h"
#include "SkeletonResource.h"
#include "ThirdPersonCharacter.h"
template<> SmartPointer<GameApp> Singleton<GameApp>::_instance = nullptr;
GameApp::GameApp()
	:m_pGameRuntime(nullptr)
{
}


GameApp::~GameApp()
{
}

void GameApp::SetupScene()
{
	std::string fileName = "";
	IAsset* pAsset = AssetManager::GetInstance()->LoadAsset("./data/1231.scene.xml");
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

	pCamera->m_pTransform->SetTranslate(Vector3(0.0f, 200.0f, -350.0f));
	pCamera->m_pTransform->SetOrientation(AngleToRad(28.0f), 0, 0);
	//
	m_pGameRuntime = m_pWorld->m_pRoot->addModule<GameRuntime>().get();
	m_pGameRuntime->m_pCamera = pCameraModule->m_pOwnerObj;
	//
	CharacterController* pCtrler;// = m_pGameRuntime->createCharacterController("./data/fbx/kulou.FBX");
	//IAsset* pAniAsset = AssetManager::GetInstance()->LoadAsset("./data/fbx/kulouanim/Mercury_LLA.animation.xml");
	//AnimationResource* pAniRes = pAniAsset->GetResource<AnimationResource>();
	////
	//AnimationTrack* pTrack = new AnimationTrack(pAniRes);
	//SkeletonModule* pSkeleton = pCtrler->m_pObj->GetModule<SkeletonModule>();// ->AddAnimationTrack(pTrack);
	//pSkeleton->AddAnimationTrack(pTrack);
	//pSkeleton->m_pDefaultTrack = pTrack;
	//
	pCtrler = m_pGameRuntime->createCharacterController("./data/prefab/deadplayer.prefab.xml");

	pCtrler->m_pObj->m_pTransform->SetTranslate(pCtrler->m_pObj->m_pTransform->GetLocalTranslate() + Vector3(10, 50, 100));



	ThirdPersonCharacter* pPerson = m_pGameRuntime->createThirdPerson("./data/fbx/kulou.FBX");
	//pPerson->m_pObj->m_pTransform->SetTranslate(pPerson->m_pObj->m_pTransform->GetLocalTranslate() + Vector3(10, 0, 100));

	//
}

void GameApp::UpdateInput()
{
	if (IsFocus() == false)
	{
		return;
	}
	m_pGameRuntime->UpdateInput();
}
