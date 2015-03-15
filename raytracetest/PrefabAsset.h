#pragma once
#include "IAsset.h"
class PrefabAsset :
	public IAsset
{
public:
	PrefabAsset();
	virtual ~PrefabAsset();

	virtual void Release(bool bReleaseResource);

};

