#include "stdafx.h"
#include "AnimationResource.h"
#include "AnimationCurve.h"
template class MAIN_API  Singleton < ResourceManager<AnimationResource> >;
SmartPointer<ResourceManager<AnimationResource>> Singleton<ResourceManager<AnimationResource>>::_instance = nullptr;
ZG::AnimationResource::AnimationResource()
	:m_bIsSkinAnimation(false)
	, m_eAniMode(EANILOOP)
{

}

ZG::AnimationResource::~AnimationResource()
{

}

AnimationCurveBase* ZG::AnimationResource::getCurveByName(std::string strName)
{
	std::unordered_map<std::string, SmartPointer<AnimationCurveBase>>::iterator iter = m_mapCurves.begin();
	iter = m_mapCurves.find(strName);
	if (iter != m_mapCurves.end())
	{
		return iter->second.get();
	}
	return nullptr;
}

void ZG::AnimationResource::AddCurve(std::string strName, AnimationCurveBase* pCurve)
{
	m_mapCurves[strName] = pCurve;
}
