#pragma once
#include "Singleton.h"
#include "IOInterface.h"
class MAIN_API IOManager :public Singleton<IOManager>
{
public:
	IOManager();
	virtual ~IOManager();
	

	shared_ptr<IOInterface> m_pIO;
};

extern template class MAIN_API  Singleton < IOManager >;