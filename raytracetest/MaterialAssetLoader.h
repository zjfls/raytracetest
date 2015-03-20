#pragma once
#include "IAssetLoader.h"
class MaterialAssetLoader :
	public IAssetLoader
{
public:
	MaterialAssetLoader();
	~MaterialAssetLoader();


	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
};

