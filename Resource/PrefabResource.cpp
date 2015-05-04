#include "stdafx.h"
#include "PrefabResource.h"

template<> shared_ptr<ResourceManager<PrefabResource>> Singleton<ResourceManager<PrefabResource>>::_instance = nullptr;

PrefabResource::PrefabResource()
	:m_pRoot(nullptr)
{
}


PrefabResource::~PrefabResource()
{
}


