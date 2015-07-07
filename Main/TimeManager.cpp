#include "stdafx.h"
#include "TimeManager.h"
#include <time.h>
#include "RenderStatistics.h"
template class MAIN_API Singleton < TimeManager > ;
template<> SmartPointer<TimeManager> Singleton<TimeManager>::_instance = nullptr;

TimeManager::TimeManager()
{
	m_fLastFrameTime = 0.0f;
	m_fFpsTimeCounter = 1.0f;
	m_nFpsCount = 0;
	m_nFps = 0;
}


TimeManager::~TimeManager()
{

}

void TimeManager::Update()
{
	clock_t curClock = clock();
	float curTime = (float)curClock / CLOCKS_PER_SEC;
	m_fThisFrameTime = curTime;
	m_fElapseTime = curTime - m_fLastFrameTime;
	m_fLastFrameTime = curTime;
	m_fFpsTimeCounter -= m_fElapseTime;
	m_nFpsCount++;
	if (m_fFpsTimeCounter <= 0)
	{
		m_fFpsTimeCounter += 1.0f;
		m_nFps = m_nFpsCount;
		m_nFpsCount = 0;
		std::cout << "fps:" << m_nFps << "drawcall:" << RenderStatistics::GetInstance()->m_nDrawCall << "Triangle:" << RenderStatistics::GetInstance()->m_nTriangleNum<< std::endl;
	}
	RenderStatistics::GetInstance()->Reset();
	
	
}
