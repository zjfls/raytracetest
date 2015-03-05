#pragma once
#include "IAssetLoader.h"
class FbxFileLoader :
	public IAssetLoader
{
public:

	FbxFileLoader()
	{
	}

	virtual ~FbxFileLoader()
	{
	}

	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
};

