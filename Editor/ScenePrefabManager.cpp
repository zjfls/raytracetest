#include "stdafx.h"
#include "ScenePrefabManager.h"

template class EDITOR_API Singleton < ScenePrefabManager >;
template<> SmartPointer<ScenePrefabManager> Singleton<ScenePrefabManager>::_instance = nullptr;


ZG::ScenePrefabManager::ScenePrefabManager()
{

}

ZG::ScenePrefabManager::~ScenePrefabManager()
{

}

void ZG::ScenePrefabManager::OnAddPrefabRes(IWorldObj* pObj, std::string)
{

}

void ZG::ScenePrefabManager::Clear()
{

}
