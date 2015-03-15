#pragma once
#include "IAssetLoader.h"
class MeshFileLoader :
	public IAssetLoader
{
public:
	
	virtual ~MeshFileLoader();

	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
private:
	MeshFileLoader();
	friend class AssetManager;
};

