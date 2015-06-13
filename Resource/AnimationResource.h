#pragma once
#include "IResource.h"
#include "Singleton.h"
#include "ResourceManager.h"
//
namespace ZG
{
	class AnimationCurve;
	class AnimationResource :public IResource
	{
	public:
		AnimationResource();
		virtual ~AnimationResource();


		std::unordered_map<std::string, SmartPointer<AnimationCurve>> m_mapCurves;
	};
	RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<AnimationResource> >;
}


