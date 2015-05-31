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

	//
	template<class T>
	bool	SetArg(std::string strName, const T& arg);
	//
	std::unordered_map<string, MaterialArg*> m_matArgs;
	virtual shared_ptr<MaterialResource> clone(){ return nullptr; };
protected:
	MaterialResource();
	friend class ResourceManager < MaterialResource > ;
public:
	ERENDERTYPEFILTER m_eFillter;
};

template<class T>
bool MaterialResource::SetArg(std::string strName, const T& arg)
{
	if (m_matArgs.find(strName) == std::end(m_matArgs))
	{
		return false;
	}
	TMatArg<T>* pArg = dynamic_cast<TMatArg<T>*>(m_matArgs[strName]);
	if (pArg == nullptr)
	{
		return false;
	}
	pArg->m_Data = arg;
	return true;
}

RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<MaterialResource> > ;

//extern template shared_ptr<ResourceManager<MaterialResource>> Singleton<ResourceManager<MaterialResource>>::_instance;