#include "stdafx.h"
#include "IntersectTest.h"
#include "Vector3.h"
#include "AABBBox.h"
#include <iostream>

bool ZG::IntersectTest::AABBBox_AABBBoxTest(const AABBBox& a, const AABBBox& b)
{
	Vector3 vecCA = a.m_Max + a.m_Min;
	vecCA = vecCA * 0.5f;
	Vector3 vecCB = b.m_Max + b.m_Min;
	vecCB = vecCB * 0.5f;
	Vector3 diffCA = a.m_Max - a.m_Min;
	diffCA = diffCA * 0.5f;
	Vector3 diffCB = b.m_Max - b.m_Min;
	diffCB = diffCB * 0.5f;

	Vector3 diffCenter = vecCB - vecCA;
	if (fabs(diffCenter.m_fx) > fabs(diffCA.m_fx + diffCB.m_fx))
	{
		//std::cout << "cull x" << std::endl;
		return false;
	}
	if (fabs(diffCenter.m_fy) > fabs(diffCA.m_fy + diffCB.m_fy))
	{
		//std::cout << "cull y" << std::endl;
		return false;
	}
	if (fabs(diffCenter.m_fz) > fabs(diffCA.m_fz + diffCB.m_fz))
	{
		//std::cout << "cull z" << std::endl;
		return true;
	}
	return true;
}

ZG::IntersectTest::IntersectTest()
{

}

ZG::IntersectTest::~IntersectTest()
{

}
