#pragma once
class IAsset;
class MAIN_API IAssetLoader
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

