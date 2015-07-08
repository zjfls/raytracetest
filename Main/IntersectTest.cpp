#include "stdafx.h"
#include "IntersectTest.h"
#include "Ray3D.h"
#include "Sphere3D.h"
#include "Plane3D.h"
#include "Mesh.h"
#include "MeshResource.h"
#include "Triangle.h"
#include "Transform.h"
#include "AABBBox.h"
#include "IWorldObj.h"
#include "Transform.h"
#include "Matrix44.h"


IntersectTest::IntersectTest()
{
}


IntersectTest::~IntersectTest()
{
}

IntersectResults IntersectTest::testRaySphere(const Ray3D& r, const Sphere3D& s, Transform& trans)
{
	//r.m_vecDirection.normalize();
	bool bInside = false;
	IntersectResults results;
	Vector3 vecDir = trans.GetWorldTranslate() - r.m_vecPos;
	//vecDir.normalize();
	float fLengthToSphere = vecDir.length();
	if (fLengthToSphere < s.m_fRadius)
	{
		bInside = true;
		return results;
	}
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



	
	IntersectData interData;
	interData.fDist = fDot - fHalfTransLength;
	interData.vecPos = r.m_vecPos + interData.fDist * r.GetDir();
	Vector3 vecNormal = interData.vecPos - trans.GetWorldTranslate();
	vecNormal.normalize();
	interData.vecNormal = vecNormal;
	results.m_vecIntersetDatas.push_back(interData);

	//double face
	//if (fHalfTransLength > 0.0001)
	//{
	//	interData.fDist = fDot + fHalfTransLength;
	//	interData.vecPos = r.m_vecPos + interData.fDist * r.GetDir();
	//	interData.vecNormal = interData.vecPos - trans.GetWorldTranslate();
	//	interData.vecNormal.normalize();
	//	results.m_vecIntersetDatas.push_back(interData);
	//}



	return results;
}

IntersectResults IntersectTest::testRayRenderables(const Ray3D& r,SmartPointer<IRenderable> pRend, Transform& trans)
{
	IntersectResults results;
	SmartPointer<Sphere3D> pSphere = pRend.SmartPointerCast<Sphere3D>();
	if (pSphere != nullptr)
	{
		results = testRaySphere(r, *pSphere, trans);
	}
	SmartPointer<Plane3D> pPlane = pRend.SmartPointerCast<Plane3D>();
	if (pPlane != nullptr)
	{
		results = testRayPlane(r, *pPlane, trans);
	}



	//
	SmartPointer<IRenderable> pRenderable = pRend;
	if (pRenderable != nullptr)
	{
		results = testRayRenderable(r, *pRenderable, trans);
	}
	std::sort(std::begin(results.m_vecIntersetDatas), std::end(results.m_vecIntersetDatas), SortByDistance);
	return IntersectResults();
}

IntersectResults IntersectTest::testRayPlane(const Ray3D& r, const Plane3D& p, const Transform& trans)
{
	IntersectResults results;
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
	IntersectData interData;
	interData.vecPos = vecInter;
	interData.fDist = fRayDist;
	interData.vecNormal = p.m_vecNormal;
	results.m_bInterset = true;
	results.m_vecIntersetDatas.push_back(interData);
	return results;
}

bool IntersectTest::SortByDistance(const IntersectData& d1, const IntersectData& d2)
{
	return d1.fDist < d2.fDist;
}

IntersectResults IntersectTest::testRayRenderable(const Ray3D& r, const IRenderable& rend, const Transform& trans)
{
	IntersectResults results;
	int nTriangleNum = rend.GetTriangleNum();
	for (int i = 0; i < nTriangleNum; ++i)
	{
		IntersectResults tmpResult;
		Triangle tri = rend.GetWorldTriangle(i);
		tmpResult = testRayTriangle(r, tri);
		for (int i = 0; i < tmpResult.m_vecIntersetDatas.size(); ++i)
		{
			tmpResult.m_vecIntersetDatas[i].pRender = (IRenderable *)&rend;
		}
		results.appendResult(tmpResult);
	}
	if (results.m_vecIntersetDatas.size() != 0)
	{
		results.m_bInterset = true;
	}
	return results;
}


//根据克莱姆公式求解，三角形的三个点表示平面的点
IntersectResults IntersectTest::testRayTriangle(const Ray3D& r, const Triangle& tri)
{
	IntersectResults results;
	//E1
	Vector3 E1 = tri.v1 - tri.v0;
	//E2
	Vector3 E2 = tri.v2 - tri.v0;
	//P
	Vector3 P = r.GetDir().cross(E2);
	//determinant
	float det = E1.dot(P);
	//
	Vector3 T;
	if (det > 0)
	{
		T = r.m_vecPos - tri.v0;
	}
	else
	{
		T = tri.v0 - r.m_vecPos;
	}
	//
	Vector3 Q = T.cross(E1);
	//
	if (det < 0.0001f)
	{
		return results;
	}


	float u = T.dot(P);
	if (u < 0.0f || u > det)
	{
		return results;
	}
	float v = r.GetDir().dot(Q);
	if (v < 0.0f || u + v > det)
	{
		return results;
	}


	float t = E2.dot(Q);
	if (t < 0.0f)
	{
		return results;
	}
	t = t / det;
	IntersectData data;
	data.fDist = t;
	data.vecNormal = E1.cross(E2);
	data.vecPos = r.m_vecPos + r.GetDir() * t;
	if (data.vecNormal.dot(r.GetDir()) < 0)
	{
		data.bBackface = true;
	}
	else
	{
		data.bBackface = false;
	}
	results.m_vecIntersetDatas.push_back(data);
	return results;
}
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

bool ZG::IntersectTest::Ray_AABBBoxTest(const Ray3D& r, const AABBBox& b,float t0,float t1)
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	//IntersectResults results;


	float xDir = r.GetDir().m_fx;
	if (xDir == 0.0f)
	{
		xDir = 0.00001f;
	}
	//
	if (xDir > 0)
	{
		tmin = (b.m_Min.m_fx - r.m_vecPos.m_fx) / xDir;
		tmax = (b.m_Max.m_fx - r.m_vecPos.m_fx) / xDir;
	}
	else
	{
		tmin = (b.m_Max.m_fx - r.m_vecPos.m_fx) / xDir;
		tmax = (b.m_Min.m_fx - r.m_vecPos.m_fx) / xDir;
	}
	//
	float yDir = r.GetDir().m_fy;
	if (yDir == 0.0f)
	{
		yDir = 0.00001f;
	}
	//
	if (yDir > 0)
	{
		tymin = (b.m_Min.m_fy - r.m_vecPos.m_fy) / yDir;
		tymax = (b.m_Max.m_fy - r.m_vecPos.m_fy) / yDir;
	}
	else
	{
		tymin = (b.m_Max.m_fy - r.m_vecPos.m_fy) / yDir;
		tymax = (b.m_Min.m_fy - r.m_vecPos.m_fy) / yDir;
	}
	if ((tmin > tymax) || (tymin > tmax))
	{
		return false;
	}
	//
	if (tymin > tmin)
	{
		tmin = tymin;
	}
	if (tymax < tmax)
	{
		tmax = tymax;
	}
	float zDir = r.GetDir().m_fz;
	if (zDir == 0.0f)
	{
		zDir = 0.00001f;
	}
	if (zDir > 0)
	{
		tzmin = (b.m_Min.m_fz - r.m_vecPos.m_fz) / zDir;
		tzmax = (b.m_Max.m_fz - r.m_vecPos.m_fz) / zDir;
	}
	else
	{
		tzmin = (b.m_Max.m_fz - r.m_vecPos.m_fz) / zDir;
		tzmax = (b.m_Min.m_fz - r.m_vecPos.m_fz) / zDir;
	}
	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return false;
	}
	if (tzmin > tmin)
	{
		tmin = tzmin;
	}
	if (tzmax < tmax)
	{
		tmax = tzmax;
	}
	//IntersectResults results;
	
	return ((tmin < t1) && (tmax > t0));
}

bool ZG::IntersectTest::Ray_BoundingTest(const Ray3D& r, const BoundingBase& b, float t0, float t1)
{
	BoundingBase* p = (BoundingBase*)&b;
	AABBBox* pBox = dynamic_cast<AABBBox*>(p);
	if (pBox != nullptr)
	{
		return Ray_AABBBoxTest(r, *pBox, t0, t1);
	}
	return false;
}
