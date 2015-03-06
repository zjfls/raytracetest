#pragma once
#include "IResource.h"
class IAsset
{
public:
	IAsset();
	virtual ~IAsset();
	/*

	*Summary: release asset and associate resource

	*Parameters:

	*     bReleaseResource:if release associate resource


	*Return : void

	*/
	virtual void Release(bool bReleaseResource) = 0;
	std::vector<weak_ptr<IResource>> m_ResourceList;

};

