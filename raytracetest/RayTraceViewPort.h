#pragma once
class RayTraceViewPort
{
public:
	RayTraceViewPort();
	virtual ~RayTraceViewPort();



protected:
	Point3D		m_vecPlanePos;
	Direction3D	m_vecPlaneNormal;

	int			m_pixWidth;
	int			m_pixHeight;


	Point3D		m_vecPt[4];
};

