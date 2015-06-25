#pragma once
#include "IAssetLoader.h"
namespace ZG
{
	class SceneAssetLoader :
		public IAssetLoader
	{
	public:
		virtual ~SceneAssetLoader();

		IAsset* Load(string path, void* pArg /*= nullptr*/) override;
		bool	Save(IAsset* pAsset) override;

		friend class AssetManager;
	private:
		SceneAssetLoader();
	};
}


