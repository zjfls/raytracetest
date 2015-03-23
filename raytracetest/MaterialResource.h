#pragma once
#include "IResource.h"
#include "MaterialArg.h"
#include "RenderEnum.h"
template<class T>
class ResourceManager;
class MaterialResource :
	public IResource
{
public:

	virtual ~MaterialResource();
	void	AddArg(string name, MaterialArg* pArg);

	std::unordered_map<string, MaterialArg*> m_matArgs;

protected:
	MaterialResource();
	friend class ResourceManager < MaterialResource > ;
public:
	ERENDERTYPEFILTER m_eFillter;
};

