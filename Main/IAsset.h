#pragma once
#include "IResource.h"
#include <vector>
#include <unordered_map>
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

		SmartPointer<IResource>		GetResource(std::string refPath)
		{
			if (m_ResourceMap.find(refPath) != std::end(m_ResourceMap))
			{
				return m_ResourceMap[refPath].get();
			}



			return nullptr;
		}
		template<class T>
		T* GetResource();
		void			AddResource(std::string refPath, SmartPointer<IResource> pRes)
		{
			m_ResourceMap[refPath] = pRes;
		}
		void			RemoveResource(std::string refPath);
		template<class T>
		void			GetAllResource(std::vector<T*>& vecRes);
		//
		template<class T>
		unsigned int			GetResourceCount();
	protected:
		std::unordered_map<std::string, SmartPointer<IResource>> m_ResourceMap;
	public:
		std::string	m_strPath;

	};

	template<class T>
	unsigned int ZG::IAsset::GetResourceCount()
	{
		std::vector<T*>& vecRes;
		GetAllResource<T>(vecRes);
		return vecRes.size();
	}

	template<class T>
	void ZG::IAsset::GetAllResource(std::vector<T*>& vecRes)
	{
		vecRes.clear();
		for each (std::pair<std::string,SmartPointer<IResource>> p in m_ResourceMap)
		{
			T* pRes = dynamic_cast<T*>(p.second.get());
			if (pRes != nullptr)
			{
				vecRes.push_back(pRes);
			}
		}
	}
	template<class T>
	T* ZG::IAsset::GetResource()
	{
		for each (std::pair<std::string, SmartPointer<IResource>> p in m_ResourceMap)
		{
			T* pRes = dynamic_cast<T*>(p.second.get());
			if (pRes != nullptr)
			{
				return pRes;
			}
		}
		return nullptr;
	}

}