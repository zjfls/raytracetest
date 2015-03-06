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
