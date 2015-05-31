#pragma once
#include <map>
#include <vector>
#include <functional>
namespace ZG
{
	class EventBase
	{
	public:
		EventBase(){};
		virtual ~EventBase(){};
	};
	class GameObjectBase;
	template <class T>
	class Event :public EventBase
	{
	public:
		bool addEventHandler(GameObjectBase* pObj, const std::function<void(T&)>& pFunction);
		bool removeEventHandler(GameObjectBase* pObj);
		//typedef void(*HandlerFunc)(Arg*);
		virtual void operator()(T& pa)
		{
			for each (std::pair<GameObjectBase*, std::function<void(T&)>> p in m_Map)
			{

				(p.second)(pa);
			}
		}
	private:
		std::map<GameObjectBase*, std::function<void(T&)>> m_Map;
	};

	template <class T>
	bool ZG::Event<T>::removeEventHandler(GameObjectBase* pObj)
	{
		if (m_Map.find(pObj) == std::end(m_Map))
		{
			return false;
		}
		m_Map.erase(pObj);
		return true;
	}

	template <class T>
	bool ZG::Event<T>::addEventHandler(GameObjectBase* pObj, const std::function<void(T&)>& pFunction)
	{
		if (m_Map.find(pObj) != std::end(m_Map))
		{
			return false;
		}
		m_Map[pObj] = pFunction;
		return true;
	}

}
