#pragma once
#include "IAsset.h"
class VertexShaderAsset :
	public IAsset
{
public:
	VertexShaderAsset();
	virtual ~VertexShaderAsset();

	virtual void Release(bool bReleaseResource);
};

class FragShaderAsset :public IAsset
{
public:
	FragShaderAsset();
	virtual ~FragShaderAsset();
	

	virtual void Release(bool bReleaseResource);
};
