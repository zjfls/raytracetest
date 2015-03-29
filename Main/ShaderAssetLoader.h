#pragma once
#include "IAssetLoader.h"
class VertexShaderAssetLoader :
	public IAssetLoader
{
public:
	VertexShaderAssetLoader();
	virtual ~VertexShaderAssetLoader();


	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);

	
};


class FragShaderAssetLoader :
	public IAssetLoader
{
public:
	FragShaderAssetLoader();
	virtual ~FragShaderAssetLoader();


	virtual IAsset* Load(string path, void* pArg /*= nullptr*/);


};

