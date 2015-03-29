#pragma once
#include "IAsset.h"
class MAIN_API MeshAsset :
	public IAsset
{
public:
	MeshAsset();
	virtual ~MeshAsset();


	virtual void Release(bool bReleaseResource);
};

