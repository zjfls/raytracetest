#include "stdafx.h"
#include "IOManager.h"
#include "WindowsIO.h"
template class MAIN_API  Singleton < IOManager >;
template<> SmartPointer<IOManager> Singleton<IOManager>::_instance = nullptr;

IOManager::IOManager()
{
	m_pIO = SmartPointer<IOInterface>(new WindowsIO);
}


IOManager::~IOManager()
{
}
