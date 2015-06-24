#include "stdafx.h"
#include "AnimationTrack.h"
#include "AnimationResource.h"
#include "FilePath.h"
#include "TimeManager.h"
#include "Transform.h"
//

//ZG::AnimationTrack::AnimationTrack()
//	:pRes(nullptr)
//{
//	m_strName = "";
//}

ZG::AnimationTrack::AnimationTrack(AnimationResource* pRes)
	:m_bIsBind(false)
{
	m_pResource = pRes;
	m_strName = getFileNameWithoutSuffix(pRes->GetRefPath());
}

ZG::AnimationTrack::~AnimationTrack()
{

}

void ZG::AnimationTrack::SetBind(bool bBind)
{
	m_bIsBind = bBind;
}

void ZG::AnimationTrack::Start()
{
	m_fStartTime = TimeManager::GetInstance()->m_fThisFrameTime;
}

void ZG::AnimationTrack::Update()
{
	float fTime = TimeManager::GetInstance()->m_fThisFrameTime - m_fStartTime;
	float fAniTime = 0.0f;
	if (m_pResource->m_eAniMode == EANILOOP)
	{
		int n = fTime / m_pResource->m_fLegnth;
		fAniTime = fTime - m_pResource->m_fLegnth * n;
	}
	else if (m_pResource->m_eAniMode == EANIONCE)
	{
		if (fTime > m_pResource->m_fLegnth)
		{
			fAniTime = m_pResource->m_fLegnth;
		}
	}
	else if (m_pResource->m_eAniMode == EANIPINGPOING)
	{
		int n = fTime / m_pResource->m_fLegnth;
		float temp = fTime - m_pResource->m_fLegnth * n;
		if (n % 2 == 0)
		{
			fAniTime = temp;
		}
		else
		{
			fAniTime = m_pResource->m_fLegnth - temp;
		}
	}
	//std::cout << "animationTime:" << fAniTime << std::endl;
	for each (std::pair<std::string,SmartPointer<AnimationBindBase>> p in m_mapAnims)
	{
		//if (p.first == "Bip01-Pelvis")
		//{
		//	int c = 0;
		//}
		p.second->EvaluateDirect(fAniTime);

		if (p.first == "Bip01-Pelvis")
		{
			AnimationBind<stTransformData>* pTrans = (AnimationBind<stTransformData>*)p.second.get();
			//std::cout << "anirotdata:" << pTrans->m_pValue->m_vecRotation.m_fx << " " << pTrans->m_pValue->m_vecRotation.m_fy << " " << pTrans->m_pValue->m_vecRotation.m_fz << std::endl;
		}
	}
}
