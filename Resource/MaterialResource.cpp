#include "stdafx.h"
#include "MaterialResource.h"
#include "ResourceManager.h"
#include "Singleton.h"
SmartPointer<ResourceManager<MaterialResource>> Singleton<ResourceManager<MaterialResource>>::_instance = nullptr;


MaterialResource::MaterialResource()
	:m_eFillter(EFILLTEROPAUE)
{
	//for each (std::pair<string, MaterialArg*> p in m_matArgs)
	//{
	//	delete 
	//}

}


MaterialResource::~MaterialResource()
{
	std::unordered_map<string, MaterialArg*>::iterator iter = m_matArgs.begin();
	while (iter != m_matArgs.end())
	{
		delete iter->second;
		iter = m_matArgs.erase(iter);
	}
}

void MaterialResource::AddArg(string name, MaterialArg* pArg)
{
	m_matArgs[name] = pArg;
}
