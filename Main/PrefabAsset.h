#pragma once
#include "IAsset.h"
class MAIN_API PrefabAsset :
	public IAsset
{
public:
	PrefabAsset();
	virtual ~PrefabAsset();

	virtual void Release(bool bReleaseResource);

};

