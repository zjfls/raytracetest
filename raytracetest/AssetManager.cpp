#include "stdafx.h"
#include "AssetManager.h"
#include "FilePath.h"
#include "FbxFileLoader.h"
AssetManager* Singleton<AssetManager>::_instance = nullptr;

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}

IAsset* AssetManager::LoadAsset(string path, void* pArg /*= nullptr*/)
{
	string strSuff = getFileSuffix(path);
	//std::cout << strSuff.c_str() << std::endl;
	//system("pause");
	return nullptr;
}

void AssetManager::Init()
{
	AddLoader("fbx", new FbxFileLoader);
}

//
void AssetManager::AddLoader(string strSuff, IAssetLoader* pLoader)
{
	assert(pLoader != nullptr);
	m_LoaderMap[strSuff] = pLoader;
	return;
}
