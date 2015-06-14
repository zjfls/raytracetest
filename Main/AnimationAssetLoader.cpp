#include "stdafx.h"
#include "AnimationAssetLoader.h"
#include "AnimationAsset.h"

ZG::AnimationAssetLoader::~AnimationAssetLoader()
{

}

IAsset* ZG::AnimationAssetLoader::Load(string path, void* pArg /*= nullptr*/)
{
	AnimationAsset* pAsset = new AnimationAsset;
	return pAsset;
}

void ZG::AnimationAssetLoader::Save(IAsset* pAsset)
{
	AnimationAsset* pAniAsset = dynamic_cast<AnimationAsset*>(pAsset);
	//
	if (pAniAsset == nullptr)
	{
		return;
	}
	//


	//
}

ZG::AnimationAssetLoader::AnimationAssetLoader()
{

}


