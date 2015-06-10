#pragma once
#include "GameObjectBase.h"
namespace ZG
{
	class MAIN_API DepthBuffer:public GameObjectBase
	{
	public:
		DepthBuffer();
		virtual ~DepthBuffer();
		virtual bool Resize(int nWidth, int nHeight) = 0;
		int m_nWidth;
		int m_nHeight;
		int m_nDepth;
	};

}

