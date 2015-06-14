#pragma once
#pragma once
#include "Singleton.h"
namespace ZG
{
	class RenderStatistics:public Singleton<RenderStatistics>
	{
	public:
		RenderStatistics();
		virtual ~RenderStatistics();
		void Reset();

		unsigned int m_nDrawCall;
		unsigned int m_nTriangleNum;
		unsigned int m_nVertexNum;
	};
	extern template class MAIN_API  Singleton < RenderStatistics >;
}


