#pragma once


template<class T>
class Singleton
{
public:
	virtual ~Singleton(){};

	static T* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new T;
		}
		return _instance;
	}

protected:
	Singleton(){};
	static T* _instance;




};