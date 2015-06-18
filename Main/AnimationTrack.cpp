#include "stdafx.h"
#include "AnimationTrack.h"
#include "AnimationResource.h"
#include "FilePath.h"
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
