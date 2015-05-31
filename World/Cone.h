#pragma once
#include "Geometry.h"
namespace ZG
{
	class WORLD_API Cone :
		public Geometry
	{
	public:
		Cone();
		virtual ~Cone();
		void GeneratePolygon();
		float m_fRadius;
		float m_fHeight;
		int		m_nSubdivide;
	};

}

