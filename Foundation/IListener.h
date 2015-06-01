#pragma once
#include <memory>
#include <string>
class IListenerSubject;
class FOUNDATION_API IListener
{
public:
	IListener();
	virtual ~IListener();


	virtual void OnNotify(std::string msg,IListenerSubject* pSubject) = 0;
};

