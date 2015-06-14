#include "stdafx.h"
#include "RenderStatistics.h"

template class MAIN_API  Singleton < RenderStatistics >;
template<> SmartPointer<RenderStatistics> Singleton<RenderStatistics>::_instance = nullptr;

ZG::RenderStatistics::RenderStatistics()
{
	m_nDrawCall = 0;
	m_nTriangleNum = 0;
	m_nVertexNum = 0;
}

ZG::RenderStatistics::~RenderStatistics()
{

}

void ZG::RenderStatistics::Reset()
{
	m_nDrawCall = 0;
	m_nTriangleNum = 0;
	m_nVertexNum = 0;
}
