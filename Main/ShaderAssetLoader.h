#pragma once

#include "IAssetLoader.h"
namespace ZG
{
	class VertexShaderAssetLoader :
		public IAssetLoader
	{
	public:
		VertexShaderAssetLoader();
		virtual ~VertexShaderAssetLoader();


		virtual IAsset* Load(std::string path, void* pArg /*= nullptr*/);


	};


	class FragShaderAssetLoader :
		public IAssetLoader
	{
	public:
		FragShaderAssetLoader();
		virtual ~FragShaderAssetLoader();


		virtual IAsset* Load(std::string path, void* pArg /*= nullptr*/);


	};

}