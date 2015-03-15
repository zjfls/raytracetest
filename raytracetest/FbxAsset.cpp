#include "stdafx.h"
#include "FbxAsset.h"


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

std::vector<shared_ptr<IResource>> FbxAsset::GetAllResource() const
{
	std::vector<shared_ptr<IResource>> resVec;
	for each (std::pair<string, weak_ptr<IResource>> keyValue in m_ResourceMap)
	{
		resVec.push_back(keyValue.second.lock());
	}
	return resVec;
}
