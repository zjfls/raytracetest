#include "stdafx.h"
#include "AssetManager.h"
#include "FilePath.h"
#include "FbxFileLoader.h"
#include "XmlPrefabLoader.h"
#include "MeshFileLoader.h"
#include "MaterialAssetLoader.h"
#include "ShaderAssetLoader.h"
#include "TextureAssetLoader.h"
#include "AnimationAssetLoader.h"
#include "SkeletonXmlLoader.h"
#include "IAsset.h"
#include <assert.h>
#include "SceneAssetLoader.h"
#include "SkeletonResource.h"
#include "IWorldObj.h"
#include "MaterialResource.h"

template class MAIN_API  Singleton < AssetManager >;
template<> SmartPointer<AssetManager> Singleton<AssetManager>::_instance = nullptr;

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}

IAsset* AssetManager::LoadAsset(std::string path, void* pArg /*= nullptr*/)
{
	
	if (path == "")
	{
		return nullptr;
	}
	if (m_AssetMap.find(path) != std::end(m_AssetMap))
	{
		return m_AssetMap[path];
	}
	std::cout << "load:" << path.c_str() << std::endl;
	std::string strSuff = getFileSuffix(path);
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
	AddLoader("animation.xml", new AnimationAssetLoader);
	AddLoader("skeleton.xml", new SkeletonXmlLoader);
	AddLoader("scene.xml", new SceneAssetLoader);


	return true;
}

//
void AssetManager::AddLoader(std::string strSuff, IAssetLoader* pLoader)
{
	assert(pLoader != nullptr);
	m_LoaderMap[strSuff] = pLoader;
	return;
}

IAsset* AssetManager::GetAsset(std::string strPath)
{
	if (m_AssetMap.find(strPath) == std::end(m_AssetMap))
	{
		return nullptr;
	}
	return m_AssetMap[strPath];
}

bool ZG::AssetManager::Save(IAsset* pAsset)
{
	std::string path = pAsset->m_strPath;
	if (path == "")
	{
		return false;
	}
	std::cout << "load:" << path.c_str() << std::endl;
	std::string strSuff = getFileSuffix(path);
	std::transform(strSuff.begin(), strSuff.end(), strSuff.begin(), tolower);
	if (m_LoaderMap.find(strSuff) == std::end(m_LoaderMap))
	{
		std::cout << "can not find loader for suffix:" << strSuff << std::endl;
		return false;
	}
	return m_LoaderMap[strSuff]->Save(pAsset);
}

void ZG::AssetManager::ReleaseAsset(std::string path, bool bReleaseResource)
{
	std::map<std::string, IAsset*>::iterator iter = m_AssetMap.find(path);
	if (iter == m_AssetMap.end())
	{
		return;
	}
	if (bReleaseResource == true)
	{
		std::vector<IResource*> vecRes;
		iter->second->GetAllResource<IResource>(vecRes);
		for each (IResource* pRes in vecRes)
		{
			ResourceManagerBase::ReleaseResource(pRes);
		}
	}
	m_AssetMap.erase(iter);
}
