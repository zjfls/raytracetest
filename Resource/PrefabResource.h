#pragma once
#include "IResource.h"
#include "ResourceManager.h"
#include "Singleton.h"
class IWorldObj;
class RESOURCE_API PrefabResource :public IResource
{
public:
	virtual ~PrefabResource();
	//IWorldObj* Initiate();
	shared_ptr<IWorldObj> GetRoot() const { return m_pRoot; }
private:
	PrefabResource();
	friend class ResourceManager < PrefabResource >;
public:
	shared_ptr<IWorldObj> m_pRoot;
};

RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<PrefabResource> >;
