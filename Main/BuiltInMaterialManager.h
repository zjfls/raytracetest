#pragma once
#include "Singleton.h"
#include "MaterialResource.h"
class MAIN_API BuiltInMaterialManager:public Singleton<BuiltInMaterialManager>
{
public:
	BuiltInMaterialManager();
	virtual ~BuiltInMaterialManager();


	bool InitBuiltInMaterial();
private:
	void	CreateDefaultMaterial();
};

extern template class MAIN_API  Singleton < BuiltInMaterialManager >;