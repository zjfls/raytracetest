#pragma once
#include <memory>
#include <map>
#include <string>
namespace ZG
{
	class IListener;
	class FOUNDATION_API IListenerSubject
	{
	public:
		IListenerSubject();
		virtual ~IListenerSubject();


		virtual void AddListener(std::string strName, IListener* pListener);
		virtual void RemoveListener(std::string strName);
		virtual void NotifyListener(std::string msg, IListenerSubject* pSubject);


		std::map<std::string, IListener*> m_mapListener;

	};

}