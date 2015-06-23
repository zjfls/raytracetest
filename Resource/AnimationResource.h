#pragma once
#include "IResource.h"
#include "Singleton.h"
#include "ResourceManager.h"
//
namespace ZG
{
	enum EAnimationWarpMode
	{
		EANIONCE,
		EANILOOP,
		EANIPINGPOING
	};
	class AnimationCurveBase;
	class RESOURCE_API AnimationResource :public IResource
	{
	public:
		AnimationResource();
		virtual ~AnimationResource();



		AnimationCurveBase* getCurveByName(std::string strName);
		bool m_bIsSkinAnimation;
		std::unordered_map<std::string, SmartPointer<AnimationCurveBase>> m_mapCurves;

		EAnimationWarpMode m_eAniMode;
		float m_fLegnth;
		friend class ResourceManager < AnimationResource > ;
	};
	RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<AnimationResource> >;
}

