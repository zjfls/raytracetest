#include "stdafx.h"
#include "BuiltInResource.h"
#include "AssetManager.h"

template class MAIN_API  Singleton < BuiltInResource >;
template<> SmartPointer<BuiltInResource> Singleton<BuiltInResource>::_instance = nullptr;
//
BuiltInResource::BuiltInResource()
{
}


//
BuiltInResource::~BuiltInResource()
{
}

//
bool BuiltInResource::InitBuiltInResource()
{
	AssetManager::GetInstance()->LoadAsset("./data/material/builtin/quad.smat.xml");
	return true;
}
