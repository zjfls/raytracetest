#pragma once

template<class T>
class ResourceMananger :public Singleton<ResourceMananger<T>>
{
public:
	ResourceMananger(){};
	virtual ~ResourceMananger(){};


	T* GetResource(string path);
private:
	std::unordered_map<string, std::shared_ptr<T>> m_ResMap;
};

