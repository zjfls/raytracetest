#pragma once
#include "H:\github\raytracetest\Foundation\Singleton.h"
#pragma once
#include "Singleton.h"
class MAIN_API TimeManager :
	public Singleton<TimeManager>
{
public:
	TimeManager();
	virtual ~TimeManager();

	void Update();

public:
	float m_fElapseTime;
	float m_fLastFrameTime;
	int	  m_nFps;
	float m_fFpsTimeCounter;
	int	  m_nFpsCount;
};

extern template class MAIN_API Singleton < TimeManager >;