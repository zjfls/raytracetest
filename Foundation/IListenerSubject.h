#pragma once
#include <memory>
#include <map>
#include <string>

class IListener;
class FOUNDATION_API IListenerSubject
{
public:
	IListenerSubject();
	virtual ~IListenerSubject();
	

	virtual void AddListener(std::string strName, std::shared_ptr<IListener> pListener);
	virtual void RemoveListener(std::string strName);
	virtual void NotifyListener(std::string msg, std::shared_ptr<IListenerSubject> pSubject);


	std::map<std::string, std::shared_ptr<IListener>> m_mapListener;
	
};

