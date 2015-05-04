#pragma once
#include <memory>
class IListenerSubject;
class FOUNDATION_API IListener
{
public:
	IListener();
	virtual ~IListener();


	virtual void OnNotify(string msg,std::shared_ptr<IListenerSubject> pSubject) = 0;
};

