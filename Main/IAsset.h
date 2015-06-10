#pragma once
#include "IResource.h"
namespace ZG
{
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

		SmartPointer<IResource>		GetResource(string refPath)
		{
			if (m_ResourceMap.find(refPath) != std::end(m_ResourceMap))
			{
				return m_ResourceMap[refPath].get();
			}
			return nullptr;
		}
		void			AddResource(string refPath, SmartPointer<IResource> pRes)
		{
			m_ResourceMap[refPath] = pRes;
		}
		void			RemoveResource(string refPath);

	protected:
		std::unordered_map<string, SmartPointer<IResource>> m_ResourceMap;
	public:
		string	m_strPath;

	};

}