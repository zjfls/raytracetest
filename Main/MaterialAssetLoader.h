#pragma once
#include "IAssetLoader.h"
namespace ZG
{
	class MAIN_API MaterialAssetLoader :
		public IAssetLoader
	{
	public:
		MaterialAssetLoader();
		~MaterialAssetLoader();


		virtual IAsset* Load(std::string path, void* pArg /*= nullptr*/);
	};

}