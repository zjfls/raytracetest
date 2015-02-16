#include "stdafx.h"
#include "IntersectTest.h"
#include "Ray3D.h"
#include "Sphere3D.h"
#include "Plane3D.h"


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
	Vector3 vecDir = trans.GetWorldTranslate() - r.m_vecPos;
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
	Vector3 vecNormal = interData.vecPos - trans.GetWorldTranslate();
	vecNormal.normalize();
	interData.vecNormal = vecNormal;
	results.m_vecIntersetDatas.push_back(interData);
	if (fHalfTransLength > 0.0001)
	{
		interData.fDist = fDot + fHalfTransLength;
		interData.vecPos = r.m_vecPos + interData.fDist * r.GetDir();
		interData.vecNormal = interData.vecPos - trans.GetWorldTranslate();
		interData.vecNormal.normalize();
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
	Plane3D* pPlane = dynamic_cast<Plane3D*>(pRend);
	if (pPlane != nullptr)
	{
		return testRayPlane(r, *pPlane, trans);
	}

	return IntersetResults();
}

IntersetResults IntersectTest::testRayPlane(const Ray3D& r, const Plane3D& p, const Transform& trans)
{
	IntersetResults results;
	Vector3 vecPlaneNormal = p.m_vecNormal;
	//plane pos to ray pos
	Vector3 vecTemp1 = r.m_vecPos - p.m_vecPt;
	float fDistRayToNormal = vecTemp1.dot(vecPlaneNormal);

	float fCosRayToNormal = -r.GetDir().dot(vecPlaneNormal);
	if (fCosRayToNormal == 0.0f)
	{
		return results;
	}
	//Vector3 vecPosRayProjPlane = r.m_vecPos - fDistRayToNormal * vecPlaneNormal;
	float fRayDist = fDistRayToNormal / fCosRayToNormal;
	if (fRayDist <= 0)
	{
		return results;
	}
	Vector3 vecInter = r.m_vecPos + r.GetDir() * fRayDist;
	IntersetData interData;
	interData.vecPos = vecInter;
	interData.fDist = fRayDist;
	interData.vecNormal = p.m_vecNormal;
	results.m_bInterset = true;
	results.m_vecIntersetDatas.push_back(interData);
	return results;
}
