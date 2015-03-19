_instance
#include "stdafx.h"
#include "MaterialResource.h"
ResourceManager<MaterialResource>* Singleton<ResourceManager<MaterialResource>>::_instance = nullptr;

MaterialResource::MaterialResource()
{
}


MaterialResource::~MaterialResource()
{
}

void MaterialResource::AddArg(string name, MaterialArg* pArg)
{
	m_matArgs[name] = pArg;
}
