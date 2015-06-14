#pragma once
#include "IAssetLoader.h"
namespace ZG
{
	class MAIN_API AnimationAssetLoader :public IAssetLoader
	{
	public:
		AnimationAssetLoader();
		virtual ~AnimationAssetLoader();

		IAsset* Load(string path, void* pArg /*= nullptr*/) override;
		void	Save(IAsset* pAsset) override;
	};

}

