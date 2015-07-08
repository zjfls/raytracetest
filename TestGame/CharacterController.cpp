#include "stdafx.h"
#include "CharacterController.h"
#include "IAsset.h"
#include "AssetManager.h"
#include "AnimationResource.h"
#include "AnimationTrack.h"
#include "skeleton.h"
#include "IWorldObj.h"
#include "SkeletonResource.h"
CharacterController::CharacterController()\
	:m_pObj(nullptr)
{

}


CharacterController::~CharacterController()
{

}

void CharacterController::LoadAnimation(std::string strName, std::string path)
{
	IAsset* pAniAsset = AssetManager::GetInstance()->LoadAsset(path);
	AnimationResource* pAniRes = pAniAsset->GetResource<AnimationResource>();
	//
	AnimationTrack* pTrack = new AnimationTrack(pAniRes);
	SkeletonModule* pSkeleton = m_pObj->GetModule<SkeletonModule>();// ->AddAnimationTrack(pTrack);
	m_pAnimations[strName] = pTrack;
	pSkeleton->AddAnimationTrack(pTrack);
}

void CharacterController::PlayAnimation(std::string strName)
{
	SkeletonModule* pSkeleton = m_pObj->GetModule<SkeletonModule>();
	if (pSkeleton != nullptr)
	{
		pSkeleton->PlayAnimation(m_pAnimations[strName]);
	}
	curAnimation = strName;
}
