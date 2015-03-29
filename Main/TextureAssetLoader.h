#pragma once
#include "IAssetLoader.h"
class TextureAssetLoader :
	public IAssetLoader
{
public:
	TextureAssetLoader();
	~TextureAssetLoader();
	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
};

