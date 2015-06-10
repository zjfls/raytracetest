#pragma once
#include "Vector3.h"
namespace ZG
{
	class MATH_API Ray3D
	{
	public:
		//Ray3D();
		Ray3D(Point3D pos, Direction3D dir);
		virtual ~Ray3D();

		void	SetDir(const Vector3& dir);
		Vector3	GetDir()const{ return m_vecDirection; };
		//////////////////////////////////////////////////////
		//
		Point3D m_vecPos;
	private:
		Direction3D m_vecDirection;
	};

}