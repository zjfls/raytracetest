#pragma once
#include "Singleton.h"
class ResourceManagerBase
{
protected:
	ResourceManagerBase(){};
public:
	virtual ~ResourceManagerBase(){};


	template<class T>
	T* CreateResource()
	{
		return T;
	}

};

template<class T>
class ResourceManager :public Singleton<ResourceManager<T>>
{
public:
	ResourceManager(){};
	virtual ~ResourceManager(){};

	//template<class U>
	shared_ptr<T>	GetResource(string path);
	template<class U>
	shared_ptr<U>	CreateResource(string refPath);
	template<class U>
	shared_ptr<U>	CreateResource();

	//void			ClearAll();
	void			RemoveResource(string refPath);
private:
	std::unordered_map<string, std::shared_ptr<T>> m_ResMap;
};

template<class T>
void ResourceManager<T>::RemoveResource(string refPath)
{
	std::unordered_map<string, std::shared_ptr<T>>::iterator iter = m_ResMap.find(refPath);
	if (iter != std::end(m_ResMap))
	{
		m_ResMap.erase(iter);
	}
}

//template<class T>
//void ResourceManager<T>::ClearAll()
//{
//	std::unordered_map<string, std::shared_ptr<T>>::iterator iter = m_ResMap.begin();
//	while (iter != m_ResMap.end())
//	{
//		iter = m_ResMap.erase(iter);
//	}
//}

template<class T> template<class U>
shared_ptr<U> ResourceManager<T>::CreateResource()
{
	shared_ptr<U> pRes(new U);
	char temp[128];
	sprintf_s(temp, 128, "memoryres:%d", (int)pRes.get());
	pRes->m_refPath = temp;
	m_ResMap[pRes->m_refPath] = pRes;
	std::cout << "create resource:" << pRes->m_refPath.c_str() << std::endl;
	return pRes;
}

template<class T> template<class U>
shared_ptr<U> ResourceManager<T>::CreateResource(string refPath)
{
	shared_ptr<U> pRes(new U);
	pRes->m_refPath = refPath;
	m_ResMap[refPath] = pRes;
	//std::cout << "create resource:" << refPath.c_str() << std::endl;
	return pRes;
}

template<class T>
shared_ptr<T> ResourceManager<T>::GetResource(string path)
{
	if (m_ResMap.find(path) == std::end(m_ResMap))
	{
		return shared_ptr<T>(nullptr);
	}
	return m_ResMap[path];
}

