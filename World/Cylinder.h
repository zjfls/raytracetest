#pragma once
#include "Geometry.h"
#include "SmartPointer.h"
namespace ZG
{
	class WORLD_API Cylinder :
		public Geometry
	{
	public:
		Cylinder();
		virtual ~Cylinder();
		void GeneratePolygon();

		float m_fRadius;
		float m_fHeight;
		int		m_nSubdivide;
	};
}

