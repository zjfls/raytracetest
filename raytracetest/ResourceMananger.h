#pragma once

template<class T>
class ResourceMananger :public Singleton<ResourceMananger<T>>
{
public:
	ResourceMananger(){};
	virtual ~ResourceMananger(){};


	shared_ptr<T> GetResource(string path);
	void	AddResource(string refPath, shared_ptr<T> pRes);
private:
	std::unordered_map<string, std::shared_ptr<T>> m_ResMap;
};

template<class T>
void ResourceMananger<T>::AddResource(string refPath, shared_ptr<T> pRes)
{
	m_ResMap[refPath] = shared_ptr<T>(pRes);
	std::cout << "add resource:" << refPath.c_str() << std::endl;
}

template<class T>
shared_ptr<T> ResourceMananger<T>::GetResource(string path)
{
	if (m_ResMap.find(path) == std::end(m_ResMap))
	{
		return nullptr;
	}	
	return m_ResMap[path];
	//shared_ptr<int> p;
	//p.get();
}

