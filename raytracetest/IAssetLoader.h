#pragma once
class IAsset;
class IAssetLoader
{
public:

	IAssetLoader()
	{
		m_pAsset = nullptr;
	}

	virtual ~IAssetLoader()
	{
	}


	virtual IAsset* Load(string path, void* pArg /*= nullptr*/) = 0;


	IAsset* m_pAsset;
};

