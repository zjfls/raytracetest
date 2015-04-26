#include "stdafx.h"
#include "AssetManager.h"
#include "FilePath.h"
#include "FbxFileLoader.h"
#include "XmlPrefabLoader.h"
#include "MeshFileLoader.h"
#include "MaterialAssetLoader.h"
#include "ShaderAssetLoader.h"
#include "TextureAssetLoader.h"
#include <assert.h>
template class MAIN_API  Singleton < AssetManager >;
template<> shared_ptr<AssetManager> Singleton<AssetManager>::_instance = nullptr;

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}

IAsset* AssetManager::LoadAsset(string path, void* pArg /*= nullptr*/)
{
	std::cout << "load:" << path.c_str() << std::endl;
	if (path == "")
	{
		return nullptr;
	}
	if (m_AssetMap.find(path) != std::end(m_AssetMap))
	{
		return m_AssetMap[path];
	}
	string strSuff = getFileSuffix(path);
	std::transform(strSuff.begin(), strSuff.end(), strSuff.begin(), tolower);
	if (m_LoaderMap.find(strSuff) == std::end(m_LoaderMap))
	{
		std::cout << "can not find loader for suffix:" << strSuff << std::endl;
		return nullptr;
	}
	IAsset* pAsset = m_LoaderMap[strSuff]->Load(path, pArg);
	if (pAsset == nullptr)
	{
		return nullptr;
	}
	m_AssetMap[path] = pAsset;
	return pAsset;
}

bool AssetManager::Init()
{
	AddLoader("fbx", new FbxFileLoader);
	AddLoader("prefab.xml", new XmlPrefabLoader);
	AddLoader("mesh", new MeshFileLoader);
	AddLoader("smat.xml", new MaterialAssetLoader);
	AddLoader("vsm", new VertexShaderAssetLoader);
	AddLoader("fsm", new FragShaderAssetLoader);
	AddLoader("srf", new FragShaderAssetLoader);
	AddLoader("tga", new TextureAssetLoader);
	AddLoader("png", new TextureAssetLoader);


	return true;
}

//
void AssetManager::AddLoader(string strSuff, IAssetLoader* pLoader)
{
	assert(pLoader != nullptr);
	m_LoaderMap[strSuff] = pLoader;
	return;
}

IAsset* AssetManager::GetAsset(string strPath)
{
	if (m_AssetMap.find(strPath) == std::end(m_AssetMap))
	{
		return nullptr;
	}
	return m_AssetMap[strPath];
}
