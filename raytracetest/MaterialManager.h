#pragma once
#include "Singleton.h"
class MaterialManager:public Singleton<MaterialManager>
{
public:
	MaterialManager();
	virtual ~MaterialManager();
};

