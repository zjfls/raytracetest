#pragma once
class IListenerSubject;
class FOUNDATION_API IListener
{
public:
	IListener();
	virtual ~IListener();


	virtual void OnNotify(string msg,IListenerSubject* pSubject) = 0;
};

