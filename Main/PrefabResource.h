#pragma once
#include "IResource.h"
#include "ResourceManager.h"
#include "Singleton.h"
namespace ZG
{
	class IWorldObj;
	class MAIN_API PrefabResource :public IResource
	{
	public:
		virtual ~PrefabResource();
		//IWorldObj* Initiate();
		SmartPointer<IWorldObj> GetRoot() const { return m_pRoot; }
	private:
		PrefabResource();
		friend class ResourceManager < PrefabResource > ;
	public:
		SmartPointer<IWorldObj> m_pRoot;
	};

	extern template class MAIN_API  Singleton < ResourceManager<PrefabResource> >;
}