#pragma once
#include "IAsset.h"
class MeshAsset :
	public IAsset
{
public:
	MeshAsset();
	virtual ~MeshAsset();


	virtual void Release(bool bReleaseResource);
};

