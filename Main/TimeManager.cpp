#include "stdafx.h"
#include "TimeManager.h"
template class MAIN_API Singleton < TimeManager > ;
template<> shared_ptr<TimeManager> Singleton<TimeManager>::_instance = nullptr;

TimeManager::TimeManager()
{

}


TimeManager::~TimeManager()
{

}
