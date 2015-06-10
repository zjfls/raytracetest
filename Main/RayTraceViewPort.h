#pragma once
namespace ZG
{
	class RayTraceCamera;
	class RayTraceViewPort
	{
	public:
		RayTraceViewPort();
		virtual ~RayTraceViewPort();
		virtual void OnTransformChanged(const RayTraceCamera* pCamera);


	public:
		Point3D		m_vecPlanePos;
		Direction3D	m_vecPlaneNormal;

		int			m_pixWidth;
		int			m_pixHeight;


		Point3D		m_vecPt[4]; //tl tr bl br
	};

}