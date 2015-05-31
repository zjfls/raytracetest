#pragma once
#include "event.h"
#include <map>
//
namespace ZG
{
	class FOUNDATION_API GameObjectBase
	{
	public:
		GameObjectBase();
		virtual ~GameObjectBase();



		bool addEvent(std::string, EventBase* pEvent);
		template<class T>
		Event<T>*	getEvent(std::string eventName);
	private:
		//
		std::map<std::string, EventBase*> m_EventMap;
		//
	public:
		unsigned int m_nRefCount;

	};

	template<class T>
	Event<T>
		* GameObjectBase::getEvent(std::string eventName)
	{
		if (m_EventMap.find(eventName) == std::end(m_EventMap))
		{
			return nullptr;
		}

		Event<T>* pEvent = dynamic_cast<Event<T>*>(m_EventMap[eventName]);
		return pEvent;
	}



}