#pragma once
#include <iostream>
#include <thread>
#include "threadmutex.h"
template<class T>
class Singleton
{
public:
	virtual ~Singleton(){};

	static shared_ptr<T> GetInstance()
	{
		if (_instance == nullptr)
		{
			//std::lock_guard<mutex> mtx(g_SingletonMutex);
			if (_instance == nullptr)
			{
				_instance = shared_ptr<T>(new T);
			}
			//std::cout << "new singleton" << std::endl;
		}
		return _instance;
	}

protected:
	Singleton(){};
	static shared_ptr<T> _instance;
};