#pragma once
#include <iostream>
#include <thread>
#include <memory>
#include "threadmutex.h"
#include "SmartPointer.h"
using ZG::SmartPointer;
template<class T>
class Singleton
{
public:
	virtual ~Singleton(){};

	static T* GetInstance()
	{
		if (_instance == nullptr)
		{
			std::lock_guard<std::mutex> mtx(g_SingletonMutex);
			if (_instance == nullptr)
			{
				_instance = new T;
			}
			//std::cout << "new singleton" << std::endl;
		}
		return _instance.get();
	}

protected:
	Singleton(){};
	static SmartPointer<T> _instance;
};