#pragma once
#include "IResource.h"
#include "Singleton.h"
#include "ResourceManager.h"
//
namespace ZG
{
	class AnimationCurveBase;
	class RESOURCE_API AnimationResource :public IResource
	{
	public:
		AnimationResource();
		virtual ~AnimationResource();


		std::unordered_map<std::string, SmartPointer<AnimationCurveBase>> m_mapCurves;


		friend class ResourceManager < AnimationResource > ;
	};
	RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<AnimationResource> >;
}


