#include "stdafx.h"
#include "AnimationResource.h"
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
