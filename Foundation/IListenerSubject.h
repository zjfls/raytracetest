#pragma once
class IListener;
class FOUNDATION_API IListenerSubject
{
public:
	IListenerSubject();
	virtual ~IListenerSubject();
	

	virtual void AddListener(string strName, IListener* pListener);
	virtual void RemoveListener(string strName);
	virtual void NotifyListener(string msg, IListenerSubject* pSubject);


	std::map<string, IListener*> m_mapListener;
	
};

