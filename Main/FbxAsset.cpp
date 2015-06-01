#include "stdafx.h"
#include "FbxAsset.h"
#include "fbxsdk.h"


FbxAsset::FbxAsset()
{
}


FbxAsset::~FbxAsset()
{
	if (m_pFbxScene != nullptr)
	{
		m_pFbxScene->Clear();
		m_pFbxScene->Destroy(true);
		m_pFbxScene = nullptr;
	}
}

void FbxAsset::Release(bool bReleaseResource)
{

}

std::vector<SmartPointer<IResource>> FbxAsset::GetAllResource() const
{
	std::vector<SmartPointer<IResource>> resVec;
	for each (std::pair<string, SmartPointer<IResource>> keyValue in m_ResourceMap)
	{
		resVec.push_back(keyValue.second.get());
	}
	return resVec;
}
