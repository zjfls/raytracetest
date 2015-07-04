#pragma once
#include "Singleton.h"
#include "InputInterface.h"
namespace ZG
{
	class MAIN_API InputManager :public Singleton<InputManager>, public GameObjectBase
	{
	public:
		InputManager();
		virtual ~InputManager();


		SmartPointer<InputInterface> m_pIO;
	};

	extern template class MAIN_API  Singleton < InputManager > ;
}