#pragma once


template<class T>
class Singleton
{
public:
	Singleton(){};
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
	static T* _instance;

};