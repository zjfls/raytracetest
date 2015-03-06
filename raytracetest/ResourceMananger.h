#pragma once

template<class T>
class ResourceMananger :public Singleton<ResourceMananger<T>>
{
public:
	ResourceMananger(){};
	virtual ~ResourceMananger(){};


	T* GetResource(string path);
	void	AddResource(string refPath, T* pRes);
private:
	std::unordered_map<string, std::shared_ptr<T>> m_ResMap;
};

template<class T>
void ResourceMananger<T>::AddResource(string refPath, T* pRes)
{
	m_ResMap[refPath] = shared_ptr<T>(pRes);
}

template<class T>
T* ResourceMananger<T>::GetResource(string path)
{
	if (m_ResMap.find(path) == std::end(m_ResMap))
	{
		return nullptr;
	}
	return m_ResMap[path].get();
	//shared_ptr<int> p;
	//p.get();
}

