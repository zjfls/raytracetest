#pragma once
#include "IResource.h"
#include "Singleton.h"
#include "ResourceManager.h"
namespace ZG
{
	class IWorldObj;
	class RESOURCE_API SceneResource :
		public IResource
	{
	public:
		SceneResource();
		virtual ~SceneResource();

		SmartPointer<IWorldObj> m_pRoot;
		friend class ResourceManager < SceneResource > ;
	};
	RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<SceneResource> >;
}


