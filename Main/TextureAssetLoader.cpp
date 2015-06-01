#include "stdafx.h"
#include "TextureAssetLoader.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Texture2D.h"
#include "TextureAsset.h"

TextureAssetLoader::TextureAssetLoader()
{
}


TextureAssetLoader::~TextureAssetLoader()
{
}

IAsset* TextureAssetLoader::Load(string path, void* pArg /*= nullptr*/)
{
	TextureAsset* pAsset = new TextureAsset;
	pAsset->m_strPath = path;
	SmartPointer<Texture> pTextureResource;
	if ((pTextureResource = ResourceManager<Texture>::GetInstance()->GetResource(path)) != nullptr)
	{
		pAsset->AddResource(path, pTextureResource.get());
	}
	else
	{
		pTextureResource = ResourceManager<Texture>::GetInstance()->CreateResource<Texture2D>(path).get();
		pAsset->AddResource(path, pTextureResource.get());
	}
	return pAsset;
}
