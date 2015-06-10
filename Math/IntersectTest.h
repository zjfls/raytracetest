#pragma once

namespace ZG
{
	class AABBBox;
	class MATH_API IntersectTest
	{
	public:
		IntersectTest();
		virtual ~IntersectTest();



		static bool AABBBox_AABBBoxTest(const AABBBox& a, const AABBBox& b);
	};
}


