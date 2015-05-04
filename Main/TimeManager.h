#pragma once
#include "H:\github\raytracetest\Foundation\Singleton.h"
#pragma once
#include "Singleton.h"
class MAIN_API TimeManager :
	public Singleton<TimeManager>
{
public:
	TimeManager();
	virtual ~TimeManager(){};
};

extern template class MAIN_API Singleton < TimeManager >;