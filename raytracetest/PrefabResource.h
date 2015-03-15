#pragma once
#include "IResource.h"
#include "ResourceMananger.h"
class IWorldObj;
class PrefabResource:public IResource
{
public:
	virtual ~PrefabResource();
	IWorldObj* m_pRoot;

private:
	PrefabResource();
	friend class ResourceManager < PrefabResource > ;
};

