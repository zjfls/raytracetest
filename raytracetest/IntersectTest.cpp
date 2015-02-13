#include "stdafx.h"
#include "IntersectTest.h"
#include "Ray3D.h"
#include "Sphere3D.h"


IntersectTest::IntersectTest()
{
}


IntersectTest::~IntersectTest()
{
}

IntersetResults IntersectTest::testRaySphere(const Ray3D& r, const Sphere3D& s,const Transform& trans)
{
	//r.m_vecDirection.normalize();
	IntersetResults results;
	Vector3 vecDir = trans.m_vecTranslate - r.m_vecPos;
	//vecDir.normalize();
	float fLengthToSphere = vecDir.length();
	float fDot = vecDir.dot(r.GetDir());
	if (fDot < 0.0f)
	{
		return results;
	}
	float fPerpLength = fLengthToSphere * fLengthToSphere - fDot * fDot;
	fPerpLength = sqrt(fPerpLength);
	if (fPerpLength > s.m_fRadius)
	{
		return results;
	}
	results.m_bInterset = true;
	float fHalfTransLength = s.m_fRadius * s.m_fRadius - fPerpLength * fPerpLength;
	fHalfTransLength = sqrt(fHalfTransLength);

	IntersetData interData;
	interData.fDist = fDot - fHalfTransLength;
	interData.vecPos = r.m_vecPos + interData.fDist * r.GetDir();
	results.m_vecIntersetDatas.push_back(interData);
	if (fHalfTransLength > 0.0001)
	{
		interData.fDist = fDot + fHalfTransLength;
		interData.vecPos = r.m_vecPos + interData.fDist * r.GetDir();
		results.m_vecIntersetDatas.push_back(interData);
	}



	return results;
}

IntersetResults IntersectTest::testRayRenderables(const Ray3D& r,IRenderable* pRend, Transform& trans)
{
	Sphere3D* pSphere = dynamic_cast<Sphere3D*>(pRend);
	if (pSphere != nullptr)
	{
		return testRaySphere(r, *pSphere, trans);
	}
	return IntersetResults();
}
