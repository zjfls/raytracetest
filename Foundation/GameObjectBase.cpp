#include "stdafx.h"
#include "GameObjectBase.h"
using namespace ZG;

ZG::GameObjectBase::GameObjectBase()
	:m_nRefCount(0)
{
}


ZG::GameObjectBase::~GameObjectBase()
{
	for each (std::pair<std::string,EventBase*> p in m_EventMap)
	{
		delete p.second;
	}
}

bool ZG::GameObjectBase::addEvent(std::string eventName, EventBase* pEvent)
{
	if (m_EventMap.find(eventName) != std::end(m_EventMap))
	{
		return false;
	}
	m_EventMap[eventName] = pEvent;
	return true;
}
