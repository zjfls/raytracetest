#include "stdafx.h"
#include "Prefab.h"
ResourceManager<Prefab>* Singleton<ResourceManager<Prefab>>::_instance = nullptr;

Prefab::Prefab()
	:m_pRoot(nullptr)
{
}


Prefab::~Prefab()
{
}
