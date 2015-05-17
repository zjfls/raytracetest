#include "stdafx.h"
#include "IOManager.h"
#include "WindowsIO.h"
template class MAIN_API  Singleton < IOManager >;
template<> shared_ptr<IOManager> Singleton<IOManager>::_instance = nullptr;

IOManager::IOManager()
{
	m_pIO = shared_ptr<IOInterface>(new WindowsIO);
}


IOManager::~IOManager()
{
}
