#pragma once
#include "Vector3.h"
namespace ZG
{
	class MATH_API Triangle
	{
	public:
		Triangle();
		Triangle(const Vector3& inv0, const Vector3& inv1, const Vector3& inv2)
			:v0(inv0), v1(inv1), v2(inv2)
		{

		}
		virtual ~Triangle();


		Vector3 v0, v1, v2;
	};

}