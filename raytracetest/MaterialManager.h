#pragma once
#include "Singleton.h"
class MaterialManager:public Singleton<MaterialManager>
{
public:
	virtual ~MaterialManager();


private:
	MaterialManager();
	friend class Singleton<MaterialManager>;
};

