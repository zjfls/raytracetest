#include "stdafx.h"
#include "AssetManager.h"
#include "FilePath.h"
#include "FbxFileLoader.h"
#include "XmlPrefabLoader.h"
#include "MeshFileLoader.h"
AssetManager* Singleton<AssetManager>::_instance = nullptr;

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}

IAsset* AssetManager::LoadAsset(string path, void* pArg /*= nullptr*/)
{
	if (m_AssetMap.find(path) != std::end(m_AssetMap))
	{
		return m_AssetMap[path];
	}
	string strSuff = getFileSuffix(path);
	IAsset* pAsset = m_LoaderMap[strSuff]->Load(path, pArg);
	if (pAsset == nullptr)
	{
		return nullptr;
	}
	m_AssetMap[path] = pAsset;
	return pAsset;
}

void AssetManager::Init()
{
	AddLoader("fbx", new FbxFileLoader);
	AddLoader("prefab.xml", new XmlPrefabLoader);
	AddLoader("mesh", new MeshFileLoader);
}

//
void AssetManager::AddLoader(string strSuff, IAssetLoader* pLoader)
{
	assert(pLoader != nullptr);
	m_LoaderMap[strSuff] = pLoader;
	return;
}
