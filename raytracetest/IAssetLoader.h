#pragma once
class IAsset;
class IAssetLoader
{
public:

	IAssetLoader()
	{
	}

	virtual ~IAssetLoader()
	{
	}


	virtual IAsset* Load(string path, void* pArg /*= nullptr*/) = 0;
};

