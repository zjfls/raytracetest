
#pragma once
#include "Singleton.h"
namespace ZG
{
	class MAIN_API TimeManager :
		public Singleton<TimeManager>, public GameObjectBase
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

	extern template class MAIN_API Singleton < TimeManager > ;
}