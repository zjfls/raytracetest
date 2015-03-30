#pragma once
#include "IResource.h"
#include "MaterialArg.h"
#include "RenderEnum.h"
#include "Singleton.h"
#include "ResourceManager.h"
template<class T>
class ResourceManager;
class RESOURCE_API MaterialResource :
	public IResource
{
public:

	virtual ~MaterialResource();
	void	AddArg(string name, MaterialArg* pArg);

	std::unordered_map<string, MaterialArg*> m_matArgs;
	virtual shared_ptr<MaterialResource> clone(){ return nullptr; };
protected:
	MaterialResource();
	friend class ResourceManager < MaterialResource > ;
public:
	ERENDERTYPEFILTER m_eFillter;
};
RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<MaterialResource> >;

//extern template shared_ptr<ResourceManager<MaterialResource>> Singleton<ResourceManager<MaterialResource>>::_instance;