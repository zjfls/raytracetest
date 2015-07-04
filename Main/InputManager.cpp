#include "stdafx.h"
#include "InputManager.h"
#include "WindowsInput.h"
template class MAIN_API  Singleton < InputManager >;
template<> SmartPointer<InputManager> Singleton<InputManager>::_instance = nullptr;

InputManager::InputManager()
{
	m_pIO = SmartPointer<InputInterface>(new WindowsInput);
}


InputManager::~InputManager()
{
}
