#pragma once
#include "IResource.h"
#include "ResourceMananger.h"
class IWorldObj;
class Prefab:public IResource
{
public:
	Prefab();
	virtual ~Prefab();
	IWorldObj* m_pRoot;


	friend class ResourceManager < Prefab > ;
};

