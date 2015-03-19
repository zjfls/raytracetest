#pragma once
#include "IResource.h"
template<class T>
class ResourceManager;
class MaterialResource :
	public IResource
{
public:

	virtual ~MaterialResource();
private:
	MaterialResource();
	friend class ResourceManager < MaterialResource > ;
};

