#pragma once
#include "IAsset.h"
class FbxAsset :
	public IAsset
{
public:
	FbxAsset();
	virtual ~FbxAsset();

	/*

	*Summary: release asset and associate resource

	*Parameters:

	*     bReleaseResource:if release associate resource


	*Return : void

	*/
	virtual void Release(bool bReleaseResource);
private:
	FbxScene*	m_pFbxScene;
	friend class FbxFileLoader;
};

