#pragma once
#include "IResource.h"
class MAIN_API IAsset
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
	virtual void Release(bool bReleaseResource);

	shared_ptr<IResource>		GetResource(string refPath)
	{
		if (m_ResourceMap.find(refPath) != std::end(m_ResourceMap))
		{
			return m_ResourceMap[refPath].lock();
		}
		return nullptr;
	}
	void			AddResource(string refPath, shared_ptr<IResource> pRes)
	{
		m_ResourceMap[refPath] = pRes;
	}
	void			RemoveResource(string refPath);

protected:
	std::unordered_map<string, weak_ptr<IResource>> m_ResourceMap;
public:
	string	m_strPath;

};

