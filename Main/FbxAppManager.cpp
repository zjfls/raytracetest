#include "stdafx.h"
#include "fbxsdk.h"
#include "FbxAppManager.h"
#include "AssetManager.h"
#include "ResourceManager.h"
#include "MeshResource.h"

template class MAIN_API Singleton < FbxAppManager >;
template<> shared_ptr<FbxAppManager> Singleton<FbxAppManager>::_instance = nullptr;

FbxAppManager::FbxAppManager()
{
	ResourceManager<MeshResource>::GetInstance();
}


FbxAppManager::~FbxAppManager()
{
	if (m_pFbxScene != nullptr)
	{
		m_pFbxScene->Destroy(true);
		m_pFbxScene = nullptr;
	}
	if (m_pFbxSdkManager != nullptr)
	{
		m_pFbxSdkManager->Destroy();
		m_pFbxSdkManager = nullptr;
	}
}


bool FbxAppManager::Init()
{
	if (m_pFbxSdkManager != nullptr)
	{
		m_pFbxSdkManager->Destroy();
	}
	m_pFbxSdkManager = FbxManager::Create();
	if (m_pFbxSdkManager == nullptr)
	{
		return false;
	}


	FbxIOSettings* pIoSetting = FbxIOSettings::Create(m_pFbxSdkManager,IOSROOT);
	m_pFbxSdkManager->SetIOSettings(pIoSetting);


	FbxString lPath = FbxGetApplicationDirectory();
	m_pFbxSdkManager->LoadPluginsDirectory(lPath.Buffer());

	return true;

}


