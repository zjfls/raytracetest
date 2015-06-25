#pragma once
#include "IResource.h"
#include "Singleton.h"
#include "ResourceManager.h"
namespace ZG
{
	class IWorldObj;
	class SceneResource :
		public IResource
	{
	public:
		SceneResource();
		virtual ~SceneResource();

		IWorldObj* m_pRoot;
	};
	RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<SceneResource> >;
}


