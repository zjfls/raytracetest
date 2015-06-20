#include "stdafx.h"
#include "AnimationModule.h"
#include "AnimationTrack.h"
//
ZG::AnimationModule::AnimationModule()
{

}

ZG::AnimationModule::~AnimationModule()
{

}

bool ZG::AnimationModule::PlayAnimation(std::string strName)
{
	for each (SmartPointer<AnimationTrack> pTrack in m_vecTracks)
	{
		if (pTrack->m_strName == strName)
		{

		}
	}
	return false;
}

bool ZG::AnimationModule::PlayAnimation(unsigned int index)
{
	if (m_vecTracks.size() > index)
	{

	}
	return false;
}

bool ZG::AnimationModule::PlayAnimation(AnimationTrack* pTrack)
{
	return true;
}

bool ZG::AnimationModule::AddAnimationTrack(AnimationTrack* pt)
{
	for each (SmartPointer<AnimationTrack> pTrack in m_vecTracks)
	{
		if (pTrack == pt)
		{
			return false;
		}
	}
	m_vecTracks.push_back(pt);
	return true;
}

bool ZG::AnimationModule::BindAnimation(AnimationTrack* pTrack)
{
	return true;
}

void ZG::AnimationModule::SetDefaultAnimationTrack(AnimationTrack* pTrack)
{
	AddAnimationTrack(pTrack);
	m_pDefaultTrack = pTrack;
}

void ZG::AnimationModule::OnUpdate()
{
	for each (AnimationTrack* pTrack in m_vecActiveTrack)
	{
		pTrack->Update();
	}
}

void ZG::AnimationModule::OnStart()
{
	if (m_pDefaultTrack != nullptr)
	{
		PlayAnimation(m_pDefaultTrack);
	}
}
