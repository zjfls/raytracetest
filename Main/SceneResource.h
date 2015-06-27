#pragma once
#include "IResource.h"
#include "Singleton.h"
#include "ResourceManager.h"
namespace ZG
{
	class IWorldObj;
	class MAIN_API SceneResource :
		public IResource
	{
	public:
		SceneResource();
		virtual ~SceneResource();

		SmartPointer<IWorldObj> m_pRoot;
		friend class ResourceManager < SceneResource > ;
	};
	extern template class MAIN_API  Singleton < ResourceManager<SceneResource> >;
}


