#pragma once
#include "IRenderable.h"
namespace ZG
{
	class MAIN_API Sphere3D :public IRenderable
	{
	public:
		Sphere3D(Point3D, float fRadius);
		virtual ~Sphere3D();

		////////////////////////////////////////////////
		float m_fRadius;
		int m_nSubdivide;
		void GeneratePolygon();
	private:
		Sphere3D();
		friend class IWorldObj;
	};

}
//class Sphere3DCreator :public IModuleCreator
//{
//public:
//	Sphere3DCreator();
//	virtual ~Sphere3DCreator();
//
//
//	virtual ModuleBase* CreateModule();
//};

