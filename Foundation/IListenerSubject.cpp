#include "stdafx.h"
#include "IListenerSubject.h"
#include "IListener.h"


IListenerSubject::IListenerSubject()
{
}


IListenerSubject::~IListenerSubject()
{
}

void IListenerSubject::AddListener(string strName, std::shared_ptr<IListener> pListener)
{
	if (m_mapListener.find(strName) != std::end(m_mapListener))
	{
		return;
	}
	m_mapListener[strName] = pListener;
}

void IListenerSubject::RemoveListener(string strName)
{
	//if (m_mapListener.find(strName) != std::end(m_mapListener))
	//{
		m_mapListener.erase(strName);
	//}
}

void IListenerSubject::NotifyListener(string msg, shared_ptr<IListenerSubject> pSubject)
{
	for each (std::pair<string,std::shared_ptr<IListener>> p in m_mapListener)
	{
		p.second->OnNotify(msg, pSubject);
	}
}
