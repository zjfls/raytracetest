#pragma once
#include <memory>
class IListener;
class FOUNDATION_API IListenerSubject
{
public:
	IListenerSubject();
	virtual ~IListenerSubject();
	

	virtual void AddListener(string strName, std::shared_ptr<IListener> pListener);
	virtual void RemoveListener(string strName);
	virtual void NotifyListener(string msg, std::shared_ptr<IListenerSubject> pSubject);


	std::map<string, std::shared_ptr<IListener>> m_mapListener;
	
};

