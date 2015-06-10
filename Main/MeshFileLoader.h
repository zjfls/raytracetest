#pragma once
#include "IAssetLoader.h"
namespace ZG
{
	class MeshFileLoader :
		public IAssetLoader
	{
	public:

		virtual ~MeshFileLoader();

		virtual IAsset* Load(string path, void* pArg /*= nullptr*/);
	private:
		MeshFileLoader();
		friend class AssetManager;
	};

}