#pragma once

template<class T>
class ResourceManager :public Singleton<ResourceManager<T>>
{
public:
	ResourceManager(){};
	virtual ~ResourceManager(){};


	shared_ptr<T>	GetResource(string path);
	shared_ptr<T>	CreateResource(string refPath);
	shared_ptr<T>	CreateResource();
	//void	AddResource(string refPath, shared_ptr<T> pRes);
private:
	std::unordered_map<string, std::shared_ptr<T>> m_ResMap;
};

template<class T>
shared_ptr<T> ResourceManager<T>::CreateResource()
{
	shared_ptr<T> pRes(new T);
	char temp[128];
	sprintf_s(temp,128,"memoryres:%d", (int)pRes.get());
	 pRes->m_refPath = temp;
	m_ResMap[pRes->m_refPath] = pRes;
	std::cout << "create resource:" << pRes->m_refPath.c_str() << std::endl;
	return pRes;
}

template<class T>
shared_ptr<T> ResourceManager<T>::CreateResource(string refPath)
{
	shared_ptr<T> pRes(new T);
	pRes->m_refPath = refPath;
	m_ResMap[refPath] = pRes;
	std::cout << "create resource:" << refPath.c_str() << std::endl;
	return pRes;
}

//template<class T>
//void ResourceMananger<T>::AddResource(string refPath, shared_ptr<T> pRes)
//{
//	pRes->m_refPath = refPath;
//	m_ResMap[refPath] = shared_ptr<T>(pRes);
//	std::cout << "add resource:" << refPath.c_str() << std::endl;
//}

template<class T>
shared_ptr<T> ResourceManager<T>::GetResource(string path)
{
	if (m_ResMap.find(path) == std::end(m_ResMap))
	{
		return nullptr;
	}	
	return m_ResMap[path];
	//shared_ptr<int> p;
	//p.get();
}

