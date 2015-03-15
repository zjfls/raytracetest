#include "stdafx.h"
#include "PrefabResource.h"
ResourceManager<PrefabResource>* Singleton<ResourceManager<PrefabResource>>::_instance = nullptr;

PrefabResource::PrefabResource()
	:m_pRoot(nullptr)
{
}


PrefabResource::~PrefabResource()
{
}
