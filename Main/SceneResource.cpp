#include "stdafx.h"
#include "SceneResource.h"
#include "IWorldObj.h"
template<> SmartPointer<ResourceManager<SceneResource>> Singleton<ResourceManager<SceneResource>>::_instance = nullptr;


ZG::SceneResource::SceneResource()
	//:m_pRoot(nullptr)
{

}

ZG::SceneResource::~SceneResource()
{

}
