#pragma once
#include <memory>
#include <string>
namespace ZG
{
	class IListenerSubject;
	class FOUNDATION_API IListener
	{
	public:
		IListener();
		virtual ~IListener();


		virtual void OnNotify(std::string msg, IListenerSubject* pSubject) = 0;
	};

}