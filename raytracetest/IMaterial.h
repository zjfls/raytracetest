#pragma once
#include "IResource.h"
#include "MaterialArg.h"
class IMaterial:public IResource
{
public:
	IMaterial();
	virtual ~IMaterial();


	std::unordered_map<string, MaterialArg> m_matArgs;
};

