#pragma once
#include "Geometry.h"
namespace ZG
{
	class WORLD_API Ring:public Geometry
	{
	public:
		Ring();
		virtual ~Ring();
		void GeneratePolygon();
		float m_fRadius;
		float m_fCircleRadius;
		int		m_nSubdivide;
		int		m_nCircleSubdivide;
	};
}


